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

#include "StreamWriter.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Wic {
namespace ImageFormat {
namespace Utilities {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StreamWriter::StreamWriter( IStream* pIStream ) :
    m_pIStream( pIStream )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StreamWriter::~StreamWriter( )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamWriter::WriteBytes( const std::vector<BYTE>& bytes ) const
{
    ULONG written = 0;
    HRESULT hr = m_pIStream->Write( bytes.data( ), static_cast<ULONG>( bytes.size( ) ), &written );
    if ( ( hr != S_OK ) || ( written != bytes.size( ) ) )
    {
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamWriter::WriteUInt32( const UINT32 value ) const
{
    vector<BYTE> bytes( 4 );

    bytes[ 0 ] = ( value & 0x000000FF ) >>  0;
    bytes[ 1 ] = ( value & 0x0000FF00 ) >>  8;
    bytes[ 2 ] = ( value & 0x00FF0000 ) >> 16;
    bytes[ 3 ] = ( value & 0xFF000000 ) >> 24;

    return WriteBytes( bytes );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Utilities
} // namespace ImageFormat
} // namespace Wic

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////