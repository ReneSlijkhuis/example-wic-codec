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

#include "utils.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WicFrameDecode;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WicBitmapDecoder : public ComObjectBase<IWICBitmapDecoder>
{
public:
    WicBitmapDecoder( );
    virtual ~WicBitmapDecoder( );

    // IUnknown
    HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void** ppObject );
    ULONG STDMETHODCALLTYPE AddRef( ) { return ComObjectBase::AddRef( ); }
    ULONG STDMETHODCALLTYPE Release( ) { return ComObjectBase::Release( ); }

    // IWICBitmapDecoder
    //   Required methods
    virtual HRESULT STDMETHODCALLTYPE QueryCapability( IStream* pIStream, DWORD *pCapability );
    virtual HRESULT STDMETHODCALLTYPE Initialize( IStream* pIStream, WICDecodeOptions cacheOptions );
    virtual HRESULT STDMETHODCALLTYPE GetContainerFormat( GUID* pGuidContainerFormat );
    virtual HRESULT STDMETHODCALLTYPE GetDecoderInfo( IWICBitmapDecoderInfo** ppIDecoderInfo );
    virtual HRESULT STDMETHODCALLTYPE GetFrameCount( UINT* pCount );
    virtual HRESULT STDMETHODCALLTYPE GetFrame( UINT index, IWICBitmapFrameDecode** ppIBitmapFrame );
    //   Optional methods
    virtual HRESULT STDMETHODCALLTYPE GetPreview( IWICBitmapSource** ppIBitmapSource );
    virtual HRESULT STDMETHODCALLTYPE GetThumbnail( IWICBitmapSource** ppIThumbnail );
    virtual HRESULT STDMETHODCALLTYPE GetColorContexts( UINT cCount, IWICColorContext** ppIColorContexts, UINT* pcActualCount );
    virtual HRESULT STDMETHODCALLTYPE GetMetadataQueryReader( IWICMetadataQueryReader** ppIMetadataQueryReader );
    virtual HRESULT STDMETHODCALLTYPE CopyPalette( IWICPalette* pIPalette );

private:
    ComPtr<IWICImagingFactory> m_factory;
    ComPtr<WicFrameDecode> m_frame;
    ComPtr<IStream> m_pIStream;
    CRITICAL_SECTION m_criticalSection;
    UINT m_index;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////