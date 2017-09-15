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

#include <wincodec.h>
#include <Wincodecsdk.h>

#include "utils.h"
#include "LisaImage.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WicFrameEncode;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WicBitmapEncoder : public ComObjectBase<IWICBitmapEncoder>
{
public:
    WicBitmapEncoder( );
    virtual ~WicBitmapEncoder( );

    void SetFrame( Wic::ImageFormat::Lisa::LisaImage& image );

    // IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppObject );
    ULONG STDMETHODCALLTYPE AddRef( ) { return ComObjectBase::AddRef( ); }
    ULONG STDMETHODCALLTYPE Release( ) { return ComObjectBase::Release( ); }

    // IWICBitmapEncoder
    //   Required methods
    HRESULT STDMETHODCALLTYPE Initialize( IStream* pIStream, WICBitmapEncoderCacheOption cacheOption );
    HRESULT STDMETHODCALLTYPE GetContainerFormat( GUID* pGuidContainerFormat );
    HRESULT STDMETHODCALLTYPE GetEncoderInfo( IWICBitmapEncoderInfo** ppIEncoderInfo );
    HRESULT STDMETHODCALLTYPE CreateNewFrame( IWICBitmapFrameEncode** ppIFrameEncode, IPropertyBag2** ppIEncoderOptions );
    HRESULT STDMETHODCALLTYPE Commit( void );
    //   Optional methods
    HRESULT STDMETHODCALLTYPE SetColorContexts( UINT cCount, IWICColorContext** ppIColorContext );
    HRESULT STDMETHODCALLTYPE SetPalette( IWICPalette* pIPalette );
    HRESULT STDMETHODCALLTYPE SetThumbnail( IWICBitmapSource* pIThumbnail );
    HRESULT STDMETHODCALLTYPE SetPreview( IWICBitmapSource* pIPreview );
    HRESULT STDMETHODCALLTYPE GetMetadataQueryWriter( IWICMetadataQueryWriter** ppIMetadataQueryWriter );

private:
    ComPtr<IWICImagingFactory> m_imagingFactory;
    ComPtr<IWICComponentFactory> m_componentFactory;
    ComPtr<WicFrameEncode> m_frame;
    Wic::ImageFormat::Lisa::LisaImage m_lisaImage;
    IStream* m_pIStream;
    CRITICAL_SECTION m_criticalSection;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////