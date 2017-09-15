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
//
// USAGE INSTRUCTIONS
//
// Include:
//  - LisaImage.h
//
// Link:
//  - gdiplus.lib
//
// Namespace:
//  - Wic::ImageFormat::Lisa
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Wic {
namespace ImageFormat {
namespace Lisa {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class PixelFormat
{
    Unknown = 0,
    UInt8,
    RGB24
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LisaImage
{
public:
    LisaImage( );
    virtual ~LisaImage( );

    bool Read( const std::wstring& filename );
    bool Read( IStream* pStream );
    bool Save( const std::wstring& filename ) const;
    bool Save( IStream* pStream ) const;

    bool SetImage( const UINT width,
                   const UINT height,
                   const PixelFormat pixelFormat,
                   const std::vector<BYTE>& bytes );

    void GetBytes( std::vector<BYTE>& bytes ) const;
    UINT GetWidth( ) const;
    UINT GetHeight( ) const;
    PixelFormat GetPixelFormat( ) const;
    static UINT GetBytesPerPixel( const PixelFormat pixelFormat );

private:
    PixelFormat ConvertPixelFormat( const UINT value ) const;
    UINT ConvertPixelFormat( const PixelFormat pixelFormat ) const;

    UINT m_width;
    UINT m_height;
    PixelFormat m_pixelFormat;
    std::vector<BYTE> m_bytes;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Lisa
} // namespace ImageFormat
} // namespace Wic

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////