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

#include <string>
#include <vector>
#include <atlbase.h>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Wic {
namespace ImageFormat {
namespace Utilities {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StreamReader
{
public:
    StreamReader( IStream* pIStream );
    virtual ~StreamReader( );

    static bool GetSize( IStream* pIStream, UINT64& size );
    UINT64 GetSize( ) const { return m_size; };

    bool SetPosition( const UINT64 position );

    bool ReadBytes( BYTE* buffer, const UINT size );
    bool ReadUInt16( UINT16& value );
    bool ReadUInt32( UINT32& value );
    bool ReadUInt64( UINT64& value );

private:
    CComPtr<IStream> m_pIStream;
    UINT64 m_size;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Utilities
} // namespace ImageFormat
} // namespace Wic

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////