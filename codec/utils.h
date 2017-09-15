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

#pragma once

#include <assert.h>

#include "main.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SectionLock {
public:
  SectionLock(CRITICAL_SECTION* cs) :cs_(cs) { EnterCriticalSection(cs_); }
  ~SectionLock() { LeaveCriticalSection(cs_); }
private:
  CRITICAL_SECTION* cs_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// A wrapper around a pointer to a COM object that does a Release on
// descruction. T should be a subclass of IUnknown.
template<typename T>
class ComPtr
{
public:
    ComPtr( ) : m_ptr( nullptr ) { }
    // ptr should be already AddRef'ed for this reference.
    ComPtr( T* ptr ) : m_ptr( ptr ) { }
    ~ComPtr( ) { if (m_ptr) m_ptr->Release( ); }

    T* Ptr( ) { return m_ptr; }
    T* AddRef( ) { m_ptr->AddRef( ); return m_ptr; }
    // new_ptr should be already AddRef'ed for this new reference.
    void reset( T* new_ptr ) { if ( m_ptr != nullptr ) m_ptr->Release( ); m_ptr = new_ptr; }
    // Allows to pass the the pointer as an 'out' parameter. If a non-NULL value
    // is written to it, it should be a valid pointer and already AddRef'ed for
    // this new reference.
    T** get_out_storage( ) { reset(nullptr); return &m_ptr; }
    T* operator->( ) { return m_ptr; }
    T& operator*( ) { return *m_ptr; }
private:
    T* m_ptr;

    // No copy and assign.
    ComPtr( const ComPtr& );
    void operator=( const ComPtr& );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Implements handling of object's and DLL's COM reference counts.
// T should be a subinterface of IUnknown. Templating used to avoid unnecessary
// mulitple inheritance.
template<typename T>
class ComObjectBase : public T {
public:
  ComObjectBase() {
    InterlockedIncrement(&MAIN_nObjects);
    ref_count_ = 1;
  }
  virtual ~ComObjectBase() {
    InterlockedDecrement(&MAIN_nObjects);
  }

  // IUnknown methods:
  virtual ULONG STDMETHODCALLTYPE AddRef() {
    return InterlockedIncrement(&ref_count_);
  }

  virtual ULONG STDMETHODCALLTYPE Release() {
    ULONG ret = InterlockedDecrement(&ref_count_);
    if (ret == 0)
      delete this;
    return ret;
  }

protected:
  volatile ULONG ref_count_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////