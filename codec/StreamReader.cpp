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

#include <vector>

#include "StreamReader.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Wic {
namespace ImageFormat {
namespace Utilities {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StreamReader::StreamReader( IStream* pIStream ) :
    m_pIStream( pIStream ),
    m_size( 0 )
{
    StreamReader::GetSize( m_pIStream, m_size );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StreamReader::~StreamReader( )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamReader::GetSize( IStream* pIStream, UINT64& size )
{
    STATSTG stat = { 0 };

    if ( pIStream == nullptr )
    {
        return false;
    }

    HRESULT hr = pIStream->Stat( &stat, STATFLAG_NONAME );
    if ( hr != S_OK )
    {
        return false;
    }

    size = stat.cbSize.QuadPart;

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamReader::SetPosition( const UINT64 position )
{
    LARGE_INTEGER newPosition = { 0 };
    newPosition.QuadPart = static_cast<LONGLONG>( position );

    HRESULT hr = m_pIStream->Seek( newPosition, STREAM_SEEK_SET, NULL );
    if ( hr != S_OK )
    {
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamReader::ReadBytes( BYTE* buffer, const UINT size )
{
    ULONG read = 0;
    HRESULT hr = m_pIStream->Read( buffer, size, &read );
    if ( ( hr != S_OK ) || ( read != size ) )
    {
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamReader::ReadUInt16( UINT16& value )
{
    ULONG read = 0;
    const UINT size = sizeof( UINT16 );
    vector<char> buffer( size );

    HRESULT hr = m_pIStream->Read( buffer.data( ), size, &read );
    if ( ( hr != S_OK ) || ( read != size ) )
    {
        return false;
    }

    UINT16 i0 = static_cast<BYTE>( buffer[ 0 ] );
    UINT16 i1 = static_cast<BYTE>( buffer[ 1 ] );

    value = ( i1 << 8 ) | ( i0 );
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamReader::ReadUInt32( UINT32& value )
{
    ULONG read = 0;
    const UINT size = sizeof( UINT32 );
    vector<char> buffer( size );

    HRESULT hr = m_pIStream->Read( buffer.data( ), size, &read );
    if ( ( hr != S_OK ) || ( read != size ) )
    {
        return false;
    }

    UINT32 i0 = static_cast<BYTE>( buffer[ 0 ] );
    UINT32 i1 = static_cast<BYTE>( buffer[ 1 ] );
    UINT32 i2 = static_cast<BYTE>( buffer[ 2 ] );
    UINT32 i3 = static_cast<BYTE>( buffer[ 3 ] );

    value = ( i3 << 24 ) | ( i2 << 16 ) | ( i1 << 8 ) | ( i0 );
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool StreamReader::ReadUInt64( UINT64& value )
{
    ULONG read = 0;
    const UINT size = sizeof( UINT64 );
    vector<char> buffer( size );

    HRESULT hr = m_pIStream->Read( buffer.data( ), size, &read );
    if ( ( hr != S_OK ) || ( read != size ) )
    {
        return false;
    }

    UINT64 i0 = static_cast<BYTE>( buffer[ 0 ] );
    UINT64 i1 = static_cast<BYTE>( buffer[ 1 ] );
    UINT64 i2 = static_cast<BYTE>( buffer[ 2 ] );
    UINT64 i3 = static_cast<BYTE>( buffer[ 3 ] );
    UINT64 i4 = static_cast<BYTE>( buffer[ 4 ] );
    UINT64 i5 = static_cast<BYTE>( buffer[ 5 ] );
    UINT64 i6 = static_cast<BYTE>( buffer[ 6 ] );
    UINT64 i7 = static_cast<BYTE>( buffer[ 7 ] );

    value = ( i7 << 56 ) | ( i6 << 48 ) | ( i5 << 40 ) | ( i4 << 32 ) | ( i3 << 24 ) | ( i2 << 16 ) | ( i1 << 8 ) | ( i0 );
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Utilities
} // namespace ImageFormat
} // namespace Wic

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////