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

#include "WicBitmapDecoder.h"
#include "WicFrameDecode.h"
#include "uuid.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WicBitmapDecoder::WicBitmapDecoder( ) :
    m_index( 0 )
{
    InitializeCriticalSection( &m_criticalSection );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WicBitmapDecoder::~WicBitmapDecoder( )
{
    DeleteCriticalSection( &m_criticalSection );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IUnknown

HRESULT WicBitmapDecoder::QueryInterface( REFIID riid, void** ppObject )
{
    if ( ppObject == nullptr )
    {
        return E_INVALIDARG;
    }

    *ppObject = nullptr;

    if ( !IsEqualGUID( riid, IID_IUnknown ) && !IsEqualGUID( riid, IID_IWICBitmapDecoder ) )
    {
        return E_NOINTERFACE;
    }

    this->AddRef( );
    *ppObject = static_cast<IWICBitmapDecoder*>( this );
    return S_OK;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IWICBitmapDecoder_required

HRESULT WicBitmapDecoder::QueryCapability( IStream* pIStream, DWORD* pCapability )
{
    if ( ( pIStream == nullptr ) || ( pCapability == nullptr ) )
    {
        return E_INVALIDARG;
    }

    *pCapability = WICBitmapDecoderCapabilityCanDecodeSomeImages;

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::Initialize( IStream* pIStream, WICDecodeOptions /*cacheOptions*/ )
{
    if ( pIStream == nullptr )
    {
        return E_INVALIDARG;
    }

    SectionLock l( &m_criticalSection );

    pIStream->AddRef( );
    m_pIStream.reset( pIStream );
    m_index = 0;

    if ( m_frame.Ptr( ) != nullptr )
    {
        return WINCODEC_ERR_WRONGSTATE;
    }

    ComPtr<WicFrameDecode> newWicFrame;
    if ( WicFrameDecode::CreateFromStream( m_pIStream.Ptr( ), &newWicFrame, m_index ) != S_OK )
    {
        return WINCODEC_ERR_WRONGSTATE;
    }

    m_frame.reset( newWicFrame.AddRef( ) );

    if ( m_frame.Ptr( ) == nullptr )
    {
        return WINCODEC_ERR_WRONGSTATE;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetContainerFormat( GUID* pGuidContainerFormat )
{
    if ( pGuidContainerFormat == nullptr )
    {
        return E_INVALIDARG;
    }

    *pGuidContainerFormat = GUID_ContainerFormat;

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetDecoderInfo( IWICBitmapDecoderInfo** ppIDecoderInfo )
{
    HRESULT hr;
    ComPtr<IWICImagingFactory> factory;

    {
        SectionLock l( &m_criticalSection );

        if ( m_factory.Ptr( ) == nullptr )
        {
            hr = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*) m_factory.get_out_storage( ) );
            if ( FAILED( hr ) )
            {
                return hr;
            }
        }

        factory.reset( m_factory.AddRef( ) );
    }

    ComPtr<IWICComponentInfo> componentInfo;

    hr = factory->CreateComponentInfo( CLSID_WicBitmapDecoder, componentInfo.get_out_storage( ) );
    if ( FAILED( hr ) )
    {
        return hr;
    }

    hr = componentInfo->QueryInterface( IID_IWICBitmapDecoderInfo, (void**) ppIDecoderInfo );
    if ( FAILED( hr ) )
    {
        return hr;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetFrameCount( UINT* pCount )
{
    if ( pCount == nullptr )
    {
        return E_INVALIDARG;
    }

    *pCount = 1;

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetFrame( UINT index, IWICBitmapFrameDecode** ppIBitmapFrame )
{
    if ( ppIBitmapFrame == nullptr )
    {
        return E_INVALIDARG;
    }

    SectionLock l( &m_criticalSection );

    if ( index >= 1 )
    {
        return WINCODEC_ERR_FRAMEMISSING;
    }

    if ( index != m_index )
    {
        ComPtr<WicFrameDecode> newWicFrame;
        if ( WicFrameDecode::CreateFromStream( m_pIStream.Ptr( ), &newWicFrame, index ) != S_OK )
        {
            return WINCODEC_ERR_WRONGSTATE;
        }

        m_frame.reset( newWicFrame.AddRef( ) );
        m_index = index;
    }

    if ( m_frame.Ptr( ) == nullptr )
    {
        // No initialize done
        return WINCODEC_ERR_FRAMEMISSING;
    }

    *ppIBitmapFrame = m_frame.AddRef( );

    return S_OK;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IWICBitmapDecoder_optional

HRESULT WicBitmapDecoder::GetPreview( IWICBitmapSource** /*ppIBitmapSource*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetThumbnail( IWICBitmapSource** /*ppIThumbnail*/ )
{
    return WINCODEC_ERR_CODECNOTHUMBNAIL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetColorContexts( UINT /*cCount*/, IWICColorContext** /*ppIColorContexts*/, UINT* /*pcActualCount*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::GetMetadataQueryReader( IWICMetadataQueryReader** ppIMetadataQueryReader )
{
    if ( m_frame.Ptr( ) == nullptr )
    {
        // No initialize done
        return WINCODEC_ERR_UNSUPPORTEDOPERATION;
    }

    return m_frame->GetMetadataQueryReader( ppIMetadataQueryReader );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapDecoder::CopyPalette( IWICPalette* /*pIPalette*/ )
{
    return WINCODEC_ERR_PALETTEUNAVAILABLE;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////