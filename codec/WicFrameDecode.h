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

class WicFrameDecode : public ComObjectBase<IWICBitmapFrameDecode> // Is derived from IWICBitmapSource
{
public:
    WicFrameDecode( Wic::ImageFormat::Lisa::LisaImage* pLisaImage );
    virtual ~WicFrameDecode( );

    static HRESULT CreateFromStream( IStream* pIStream, ComPtr<WicFrameDecode>* ppFrame, UINT index );

    // RawImageLib
    UINT GetFrameCount( );

    // IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppObject );
    ULONG STDMETHODCALLTYPE AddRef( ) { return ComObjectBase::AddRef( ); }
    ULONG STDMETHODCALLTYPE Release( ) { return ComObjectBase::Release( ); }

    // IWICBitmapSource
    //   Required methods
    virtual HRESULT STDMETHODCALLTYPE GetSize( UINT* pWidth, UINT* pHeight );
    virtual HRESULT STDMETHODCALLTYPE GetPixelFormat( WICPixelFormatGUID* pPixelFormat );
    virtual HRESULT STDMETHODCALLTYPE GetResolution( double* pDpiX, double* pDpiY );
    virtual HRESULT STDMETHODCALLTYPE CopyPixels( const WICRect* pRc, UINT stride, UINT bufferSize, BYTE* pBuffer );
    //   Optional methods
    virtual HRESULT STDMETHODCALLTYPE CopyPalette( IWICPalette* pIPalette );

    // IWICBitmapFrameDecode
    virtual HRESULT STDMETHODCALLTYPE GetThumbnail( IWICBitmapSource** ppIThumbnail );
    virtual HRESULT STDMETHODCALLTYPE GetColorContexts( UINT cCount, IWICColorContext** ppIColorContexts, UINT* pcActualCount );
    virtual HRESULT STDMETHODCALLTYPE GetMetadataQueryReader( IWICMetadataQueryReader** ppIMetadataQueryReader );

private:
    std::unique_ptr<Wic::ImageFormat::Lisa::LisaImage> m_pLisaImage;
    std::vector<BYTE> m_imageData;
    UINT m_width;
    UINT m_height;
    Wic::ImageFormat::Lisa::PixelFormat m_pixelFormat;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////