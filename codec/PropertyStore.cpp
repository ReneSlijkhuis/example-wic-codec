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

#include <atlbase.h>
#include <iostream>
#include <string>
#include <propsys.h>
#include <propkey.h>
#include <propvarutil.h>

#include "main.h"
#include "PropertyStore.h"
#include "LisaImage.h"

using namespace std;
using namespace Wic::ImageFormat::Lisa;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PropertyStore::PropertyStore( ) :
    m_referenceCount( 1 )
{
    InterlockedIncrement( &MAIN_nObjects );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PropertyStore::~PropertyStore( )
{
    InterlockedDecrement( &MAIN_nObjects );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IUnknown

// Query to the interface the component supported.
IFACEMETHODIMP PropertyStore::QueryInterface( REFIID riid, void **ppv )
{
    static const QITAB qit[] =
    {
        QITABENT(PropertyStore, IInitializeWithStream),
        QITABENT(PropertyStore, IPropertyStore),
        QITABENT(PropertyStore, IPropertyStoreCapabilities),
        { 0 },
    };
    return QISearch(this, qit, riid, ppv);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Increase the reference count for an interface on an object.
IFACEMETHODIMP_(ULONG) PropertyStore::AddRef( )
{
    return InterlockedIncrement( &m_referenceCount );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Decrease the reference count for an interface on an object.
IFACEMETHODIMP_(ULONG) PropertyStore::Release( )
{
    ULONG cRef = InterlockedDecrement( &m_referenceCount );
    if (0 == cRef)
    {
        delete this;
    }

    return cRef;
}

#pragma endregion
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IInitializeWithStream

// Initializes the property handler with a stream.
IFACEMETHODIMP PropertyStore::Initialize( IStream *pStream, DWORD /*grfMode*/ )
{
    if ( pStream == nullptr )
    {
        return E_INVALIDARG;
    }

    CComPtr<IStream> pLocalStream = pStream;
    if ( !m_image.Read( pLocalStream ) )
    {
        return E_FAIL;
    }

    return S_OK;
}

#pragma endregion
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IPropertyStore

IFACEMETHODIMP PropertyStore::GetCount( DWORD* pCount )
{
    if ( pCount == nullptr )
    {
        return E_POINTER;
    }

    *pCount = 4;

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP PropertyStore::GetAt( DWORD index, PROPERTYKEY* pKey )
{
    if ( pKey == nullptr )
    {
        return E_POINTER;
    }

    switch ( index )
    {
        case 0:
        {
            *pKey = PKEY_Image_HorizontalSize;
            break;
        }

        case 1:
        {
            *pKey = PKEY_Image_VerticalSize;
            break;
        }

        case 2:
        {
            *pKey = PKEY_Image_Dimensions;
            break;
        }

        case 3:
        {
            *pKey = PKEY_Image_BitDepth;
            break;
        }

        // Adapt the 'PropertyStore::GetCount()' function when new properties are added!

        default:
        {
            return E_INVALIDARG;
        }
    }

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP PropertyStore::GetValue( REFPROPERTYKEY key, PROPVARIANT* pValue )
{
    // Windows Properties
    // https://msdn.microsoft.com/en-us/library/windows/desktop/dd561977%28v=vs.85%29.aspx

    if ( pValue == nullptr )
    {
        return E_POINTER;
    }

    if ( key == PKEY_Image_HorizontalSize )
    {
        UINT width = m_image.GetWidth( );
        return InitPropVariantFromUInt32( width, pValue );
    }
    else if ( key == PKEY_Image_VerticalSize )
    {
        UINT height = m_image.GetHeight( );
        return InitPropVariantFromUInt32( height, pValue );
    }
    else if ( key == PKEY_Image_Dimensions )
    {
        UINT width = m_image.GetWidth( );
        UINT height = m_image.GetHeight( );

        wstring msg = to_wstring( width ) + L" x " + to_wstring( height );
        return InitPropVariantFromString( msg.c_str( ), pValue );
    }
    else if ( key == PKEY_Image_BitDepth )
    {
        UINT bitDepth = 0;
        PixelFormat pixelFormat = m_image.GetPixelFormat( );

        if ( pixelFormat == PixelFormat::UInt8 )
        {
            bitDepth = 8;
        }
        else if ( pixelFormat == PixelFormat::RGB24 )
        {
            bitDepth = 24;
        }
        else
        {
            return E_FAIL;
        }

        return InitPropVariantFromUInt32( bitDepth, pValue );
    }

    return E_INVALIDARG;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP PropertyStore::SetValue( REFPROPERTYKEY /*key*/, REFPROPVARIANT /*value*/ )
{
    return STG_E_ACCESSDENIED;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IFACEMETHODIMP PropertyStore::Commit( )
{
    return STG_E_ACCESSDENIED;
}

#pragma endregion
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IPropertyStoreCapabilities

IFACEMETHODIMP PropertyStore::IsPropertyWritable( REFPROPERTYKEY /*key*/ )
{
    return S_FALSE;
}

#pragma endregion
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////