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

#include <vector>
#include <wincodec.h>

#include "utils.h"
#include "LisaImage.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WicFrameEncode : public ComObjectBase<IWICBitmapFrameEncode>
{
public:
    WicFrameEncode( WicBitmapEncoder* pEncoder );
    virtual ~WicFrameEncode( );

    // IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppObject );
    ULONG STDMETHODCALLTYPE AddRef( ) { return ComObjectBase::AddRef( ); }
    ULONG STDMETHODCALLTYPE Release( ) { return ComObjectBase::Release( ); }

    // IWICBitmapFrameEncode
    //   Required methods
    virtual HRESULT STDMETHODCALLTYPE Initialize( IPropertyBag2* pIEncoderOptions );
    virtual HRESULT STDMETHODCALLTYPE SetSize( UINT width, UINT height );
    virtual HRESULT STDMETHODCALLTYPE SetResolution( double dpiX, double dpiY );
    virtual HRESULT STDMETHODCALLTYPE SetPixelFormat( WICPixelFormatGUID* pPixelFormat );
    virtual HRESULT STDMETHODCALLTYPE WritePixels( UINT lineCount, UINT cbStride, UINT cbBufferSize, BYTE* pbPixels );
    virtual HRESULT STDMETHODCALLTYPE WriteSource( IWICBitmapSource* pIBitmapSource, WICRect* pRect );
    virtual HRESULT STDMETHODCALLTYPE Commit( void );

    //   Optional methods
    virtual HRESULT STDMETHODCALLTYPE SetColorContexts( UINT cCount, IWICColorContext** ppIColorContext );
    virtual HRESULT STDMETHODCALLTYPE SetPalette( IWICPalette* pIPalette );
    virtual HRESULT STDMETHODCALLTYPE SetThumbnail( IWICBitmapSource* pIThumbnail );
    virtual HRESULT STDMETHODCALLTYPE GetMetadataQueryWriter( IWICMetadataQueryWriter** ppIMetadataQueryWriter );

private:
    WicBitmapEncoder* m_pEncoder;
    UINT m_width;
    UINT m_height;
    Wic::ImageFormat::Lisa::PixelFormat m_pixelFormat;
    Wic::ImageFormat::Lisa::LisaImage m_lisaImage;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////