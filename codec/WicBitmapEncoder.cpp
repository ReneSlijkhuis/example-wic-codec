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

#include "WicBitmapEncoder.h"
#include "WicFrameEncode.h"
#include "uuid.h"

using namespace std;
using namespace Wic::ImageFormat::Lisa;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WicBitmapEncoder::WicBitmapEncoder( ) :
    m_pIStream( nullptr )
{
    InitializeCriticalSection( &m_criticalSection );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WicBitmapEncoder::~WicBitmapEncoder( )
{
    DeleteCriticalSection( &m_criticalSection );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WicBitmapEncoder::SetFrame( LisaImage& image )
{
    m_lisaImage = image;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IUnknown

HRESULT WicBitmapEncoder::QueryInterface( REFIID riid, void** ppObject )
{
    if ( ppObject == nullptr )
    {
        return E_INVALIDARG;
    }

    *ppObject = nullptr;

    if ( IsEqualGUID( riid, IID_IWICBitmapEncoder ) )
    {
        this->AddRef( );
        *ppObject = static_cast<IWICBitmapEncoder*>( this );
        return S_OK;
    }
    else if ( IsEqualGUID( riid, IID_IUnknown ) )
    {
        this->AddRef( );
        *ppObject = static_cast<IWICBitmapEncoder*>( this );
        return S_OK;
    }

    return E_NOINTERFACE;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IWICBitmapEncoder_required

HRESULT WicBitmapEncoder::Initialize( IStream* pIStream, WICBitmapEncoderCacheOption /*cacheOption*/ )
{
    HRESULT hr = S_OK;

    if ( pIStream == nullptr )
    {
        return E_INVALIDARG;
    }

    {
        SectionLock l( &m_criticalSection );

        m_pIStream = pIStream;

        if ( m_imagingFactory.Ptr( ) == nullptr )
        {
            hr = CoCreateInstance( CLSID_WICImagingFactory,
                                   NULL,
                                   CLSCTX_INPROC_SERVER,
                                   IID_IWICImagingFactory,
                                   (LPVOID*) m_imagingFactory.get_out_storage( ) );
        }

        if ( ( m_componentFactory.Ptr( ) == nullptr ) &&
             ( m_imagingFactory.Ptr( ) != nullptr ) &&
             ( SUCCEEDED( hr ) ) )
        {
            hr = m_imagingFactory->QueryInterface( IID_IWICComponentFactory, (void**) &m_componentFactory );
            if ( SUCCEEDED( hr ) )
            {
                m_componentFactory.AddRef( );
            }
        }
    }

    return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::GetContainerFormat( GUID* pGuidContainerFormat )
{
    if ( pGuidContainerFormat == nullptr )
    {
        return E_INVALIDARG;
    }

    *pGuidContainerFormat = GUID_ContainerFormat;

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::GetEncoderInfo( IWICBitmapEncoderInfo** ppIEncoderInfo )
{
    if ( m_imagingFactory.Ptr( ) == nullptr )
    {
        return WINCODEC_ERR_NOTINITIALIZED;
    }

    HRESULT hr;
    ComPtr<IWICComponentInfo> componentInfo;

    hr = m_imagingFactory->CreateComponentInfo( CLSID_WicBitmapEncoder, componentInfo.get_out_storage( ) );
    if ( FAILED( hr ) )
    {
        return hr;
    }

    hr = componentInfo->QueryInterface( IID_IWICBitmapEncoderInfo, (void**) ppIEncoderInfo );
    if ( FAILED( hr ) )
    {
        return hr;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::CreateNewFrame( IWICBitmapFrameEncode** ppIFrameEncode, IPropertyBag2** ppIEncoderOptions )
{
    if ( ( m_imagingFactory.Ptr( ) == nullptr ) || ( m_componentFactory.Ptr( ) == nullptr ) )
    {
        return WINCODEC_ERR_NOTINITIALIZED;
    }

    if ( ppIFrameEncode == nullptr )
    {
        return E_INVALIDARG;
    }

    SectionLock l( &m_criticalSection );

    ComPtr<WicFrameEncode> output;
    output.reset( new WicFrameEncode( this ) );
    *ppIFrameEncode = output.AddRef();

    m_frame.reset( output.AddRef( ) );

    if ( ppIEncoderOptions != nullptr )
    {
        UINT propertyCount = 0;
        IPropertyBag2* pPropertyBag = NULL;
        PROPBAG2 propBag;
        ZeroMemory( &propBag, sizeof propBag );

        m_componentFactory->CreateEncoderPropertyBag( &propBag, propertyCount, ppIEncoderOptions );
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::Commit( void )
{
    if ( m_pIStream == nullptr )
    {
        return WINCODEC_ERR_NOTINITIALIZED;
    }

    if ( m_frame.Ptr( ) == nullptr )
    {
        return WINCODEC_ERR_FRAMEMISSING;
    }

    return m_lisaImage.Save( m_pIStream ) ? S_OK : E_FAIL;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IWICBitmapEncoder_optional

HRESULT WicBitmapEncoder::SetColorContexts( UINT /*cCount*/, IWICColorContext** /*ppIColorContext*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::SetPalette( IWICPalette* /*pIPalette*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::SetThumbnail( IWICBitmapSource* /*pIThumbnail*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::SetPreview( IWICBitmapSource* /*pIPreview*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicBitmapEncoder::GetMetadataQueryWriter( IWICMetadataQueryWriter** /*ppIMetadataQueryWriter*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////