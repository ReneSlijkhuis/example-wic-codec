///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    MIT License
//
//    Copyright(c) 2017 René Slijkhuis
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in all
//    copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//    SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INITGUID

#include <windows.h>

#include <new>
#include <advpub.h>
#include <shlobj.h>
#include <strsafe.h>
#include <unknwn.h>

#include "main.h"
#include "utils.h"
#include "uuid.h"
#include "WicBitmapDecoder.h"
#include "WicBitmapEncoder.h"
#include "PropertyStore.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Object and server locks counters
LONG volatile MAIN_nObjects = 0;
LONG volatile MAIN_nServerLocks = 0;
HINSTANCE g_hInst;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class factory

typedef HRESULT (*ObjectConstructor)(IUnknown** ppvObject);

// A default constructor. Creates and instance of T. T should be a subclass of
// IUnknown with a parameter-less constructor.
template<typename T>
HRESULT CreateComObject(IUnknown** output)
{
    T* result = new (std::nothrow) T();
    if ( result == nullptr )
    {
        return E_OUTOFMEMORY;
    }

    *output = reinterpret_cast<IUnknown*>( result );
    if ( *output == nullptr )
    {
        return E_NOINTERFACE;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyClassFactory : public ComObjectBase<IClassFactory>
{
public:
  MyClassFactory(ObjectConstructor ctor);
  // IUnknown:
  HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
  ULONG STDMETHODCALLTYPE AddRef() { return ComObjectBase::AddRef(); }
  ULONG STDMETHODCALLTYPE Release() { return ComObjectBase::Release(); }
  // IClassFactory:
  HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject);
  HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);

private:
  volatile LONG ref_count_;
  ObjectConstructor ctor_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MyClassFactory::MyClassFactory(ObjectConstructor ctor) {
  InterlockedIncrement(&MAIN_nObjects);
  ref_count_ = 0;
  ctor_ = ctor;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT MyClassFactory::QueryInterface(REFIID riid, void **ppvObject)
{
  if (ppvObject == NULL)
    return E_INVALIDARG;
  *ppvObject = NULL;

  if (!IsEqualGUID(riid, IID_IUnknown) && !IsEqualGUID(riid, IID_IClassFactory))
    return E_NOINTERFACE;
  this->AddRef();
  *ppvObject = static_cast<IClassFactory*>(this);
  return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT MyClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject)
{
  IUnknown* output;
  HRESULT ret;

  if (ppvObject == NULL)
    return E_INVALIDARG;
  *ppvObject = NULL;

  if (pUnkOuter != NULL)
    return CLASS_E_NOAGGREGATION;

  ret = ctor_(&output);
  if (FAILED(ret))
    return ret;
  ret = output->QueryInterface(riid, ppvObject);
  output->Release();
  if (FAILED(ret))
    ppvObject = NULL;
  return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT MyClassFactory::LockServer(BOOL fLock)
{
  if (fLock)
    InterlockedIncrement(&MAIN_nServerLocks);
  else
    InterlockedDecrement(&MAIN_nServerLocks);
  return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef HRESULT (WINAPI *RegInstallFuncA)(HMODULE hm, LPCSTR pszSection, const STRTABLEA* pstTable);
typedef void (STDAPICALLTYPE *SHChangeNotifyFunc)(LONG wEventId, UINT uFlags, LPCVOID dwItem1, LPCVOID dwItem2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static HRESULT RegisterServer( )
{
    // The installer will create the needed registry entries...

    // Updating the Thumbnail Cache When Installing Your Codec
    // When a codec is installed, the installer needs to call the following function after writing its registry entries.
    SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL );

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STDAPI DllRegisterServer( )
{
    RegisterServer( );

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STDAPI DllUnregisterServer( )
{
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STDAPI DllGetClassObject( REFCLSID clsid, REFIID iid, LPVOID *ppv )
{
    if ( ppv == nullptr )
    {
        return E_INVALIDARG;
    }

    *ppv = nullptr;

    if ( !IsEqualGUID( iid, IID_IClassFactory ) )
    {
        return E_INVALIDARG;
    }

    if ( IsEqualGUID( clsid, CLSID_WicBitmapDecoder ) )
    {
        *ppv = (LPVOID)(new (std::nothrow) MyClassFactory( CreateComObject<WicBitmapDecoder> ) );
    }
    else if ( IsEqualGUID( clsid, CLSID_WicBitmapEncoder ) )
    {
        *ppv = (LPVOID)(new (std::nothrow) MyClassFactory( CreateComObject<WicBitmapEncoder> ) );
    }
    else if ( IsEqualGUID( clsid, CLSID_PropertyStore ) )
    {
        *ppv = (LPVOID)(new (std::nothrow) MyClassFactory( CreateComObject<PropertyStore> ) );
    }
    else
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    if ( *ppv == nullptr )
    {
        return E_OUTOFMEMORY;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STDAPI DllCanUnloadNow( )
{
    if ( MAIN_nObjects == 0 && MAIN_nServerLocks == 0 )
    {
        return S_OK;
    }
    else
    {
        return S_FALSE;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL WINAPI DllMain( __in  HINSTANCE hinstDLL, __in  DWORD fdwReason, __in  LPVOID lpvReserved )
{
    if ( fdwReason == DLL_PROCESS_ATTACH )
    {
        DisableThreadLibraryCalls( hinstDLL );
        g_hInst = hinstDLL;
    }

    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////