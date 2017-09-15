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

using namespace std;
using namespace Wic::ImageFormat::Lisa;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WicFrameEncode::WicFrameEncode( WicBitmapEncoder* pEncoder ) :
    m_width( 0 ),
    m_height( 0 ),
    m_pixelFormat( PixelFormat::Unknown ),
    m_pEncoder( pEncoder )
{
    m_pEncoder->AddRef( );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WicFrameEncode::~WicFrameEncode( )
{
    m_pEncoder->Release( );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IUnknown

HRESULT WicFrameEncode::QueryInterface( REFIID riid, void** ppObject )
{
    if ( ppObject == nullptr )
    {
        return E_INVALIDARG;
    }

    *ppObject = nullptr;

    if ( IsEqualGUID( riid, IID_IWICBitmapFrameEncode ) )
    {
        this->AddRef( );
        *ppObject = static_cast<IWICBitmapFrameEncode*>( this );
        return S_OK;
    }
    else if ( IsEqualGUID( riid, IID_IUnknown ) )
    {
        this->AddRef( );
        *ppObject = static_cast<IWICBitmapFrameEncode*>( this );
        return S_OK;
    }

    return E_NOINTERFACE;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IWICBitmapFrameEncode_required

HRESULT WicFrameEncode::Initialize( IPropertyBag2* /*pIEncoderOptions*/ )
{
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::SetSize( UINT width, UINT height )
{
    m_width = width;
    m_height = height;

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::SetResolution( double /*dpiX*/, double /*dpiY*/ )
{
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::SetPixelFormat( WICPixelFormatGUID* pPixelFormat )
{
    if ( pPixelFormat == nullptr )
    {
        return E_INVALIDARG;
    }

    if ( *pPixelFormat == GUID_WICPixelFormat8bppGray )
    {
        m_pixelFormat = PixelFormat::UInt8;
    }
    else if ( *pPixelFormat == GUID_WICPixelFormat24bppRGB )
    {
        m_pixelFormat = PixelFormat::RGB24;
    }
    else
    {
        return WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::WritePixels( UINT lineCount, UINT cbStride, UINT cbBufferSize, BYTE* pbPixels )
{
    if ( pbPixels == nullptr )
    {
        return E_INVALIDARG;
    }

    if ( ( m_width == 0 ) || ( m_height == 0 ) || ( m_pixelFormat == PixelFormat::Unknown ) )
    {
        return WINCODEC_ERR_NOTINITIALIZED;
    }

    const UINT strideDestination = m_width * LisaImage::GetBytesPerPixel( m_pixelFormat );
    const UINT sizeDestination = m_height * strideDestination;

    if ( ( m_height != lineCount ) ||
         ( strideDestination < cbStride ) ||
         ( sizeDestination < cbBufferSize ) )
    {
        return E_INVALIDARG;
    }

    vector<BYTE> bytes( sizeDestination, 0x00 );
    for ( UINT i = 0 ; i < m_height ; i++ )
    {
        BYTE* pBytesSource = pbPixels + ( cbStride * i );
        BYTE* pBytesDestination = bytes.data( ) + ( strideDestination * i );
        memcpy_s( pBytesDestination, strideDestination, pBytesSource, strideDestination );
    }

    if ( !m_lisaImage.SetImage( m_width, m_height, m_pixelFormat, bytes ) )
    {
        return E_FAIL;
    }

    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::WriteSource( IWICBitmapSource* pIBitmapSource, WICRect* pRect )
{
    HRESULT hr = S_OK;

    if ( pIBitmapSource == nullptr )
    {
        return E_INVALIDARG;
    }

    if ( pRect != nullptr )
    {
        return WINCODEC_ERR_UNSUPPORTEDOPERATION;
    }

    hr = pIBitmapSource->GetSize( &m_width, &m_height );
    if ( FAILED( hr ) )
    {
        return WINCODEC_ERR_GENERIC_ERROR;
    }

    WICPixelFormatGUID pixelFormat;
    hr = pIBitmapSource->GetPixelFormat( &pixelFormat );
    if ( FAILED( hr ) )
    {
        return WINCODEC_ERR_GENERIC_ERROR;
    }

    if ( pixelFormat == GUID_WICPixelFormat8bppGray )
    {
        m_pixelFormat = PixelFormat::UInt8;
    }
    else if ( pixelFormat == GUID_WICPixelFormat24bppRGB )
    {
        m_pixelFormat = PixelFormat::RGB24;
    }
    else
    {
        return WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT;
    }

    UINT bytesPerPixel = LisaImage::GetBytesPerPixel( m_pixelFormat );
    UINT stride = m_width * bytesPerPixel;
    UINT size = m_width * m_height * bytesPerPixel;

    vector<BYTE> bytes( size );
    hr = pIBitmapSource->CopyPixels( NULL, stride, size, bytes.data( ) );
    if ( FAILED( hr ) )
    {
        return WINCODEC_ERR_GENERIC_ERROR;
    }

    return WritePixels( m_height, stride, size, bytes.data( ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::Commit( void )
{
    m_pEncoder->SetFrame( m_lisaImage );
    return S_OK;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region IWICBitmapFrameEncode_optional

HRESULT WicFrameEncode::SetColorContexts( UINT /*cCount*/, IWICColorContext** /*ppIColorContext*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::SetPalette( IWICPalette* /*pIPalette*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::SetThumbnail( IWICBitmapSource* /*pIThumbnail*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT WicFrameEncode::GetMetadataQueryWriter( IWICMetadataQueryWriter** /*ppIMetadataQueryWriter*/ )
{
    return WINCODEC_ERR_UNSUPPORTEDOPERATION;
}

#pragma endregion
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////