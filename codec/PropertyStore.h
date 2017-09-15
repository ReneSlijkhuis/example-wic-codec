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

#include <windows.h>
#include <shlobj.h>
#include <shlguid.h>
#include <propsys.h>
#include <propkey.h>

#include "LisaImage.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  This class is technically a Windows Shell Extension. The 'IPropertyStore' interface is not part of the
//  Windows Imaging Component (WIC).
//
class PropertyStore :
    public IInitializeWithStream,
    public IPropertyStore,
    public IPropertyStoreCapabilities
{
public:
    PropertyStore( );
    virtual ~PropertyStore( );

    // IUnknown
    IFACEMETHODIMP QueryInterface( REFIID riid, void **ppv );
    IFACEMETHODIMP_(ULONG) AddRef( );
    IFACEMETHODIMP_(ULONG) Release( );

    // IInitializeWithStream
    IFACEMETHODIMP Initialize( IStream *pStream, DWORD grfMode );

    // IPropertyStore
    IFACEMETHODIMP GetCount( DWORD* pCount );
    IFACEMETHODIMP GetAt( DWORD index, PROPERTYKEY* pKey );
    IFACEMETHODIMP GetValue( REFPROPERTYKEY key, PROPVARIANT* pValue );
    IFACEMETHODIMP SetValue( REFPROPERTYKEY key, REFPROPVARIANT value );
    IFACEMETHODIMP Commit( );

    // IPropertyStoreCapabilities
    IFACEMETHODIMP IsPropertyWritable( REFPROPERTYKEY key );

private:
    long m_referenceCount;
    Wic::ImageFormat::Lisa::LisaImage m_image;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////