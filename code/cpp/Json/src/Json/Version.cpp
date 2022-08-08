#include "Version.h"

Version & Version::operator=( const Version &rhs )
{

    _version[ VERSION::MAJOR ] = rhs.getMajor();
    _version[ VERSION::MINOR ] = rhs.getMinor();
    _version[ VERSION::PATCH ] = rhs.getPatch();
    _version[ VERSION::BUILD ] = rhs.getBuild();

    return *this;
}

Version &Version::operator+=( const int &incrementBuild )
{
    _version[ VERSION::BUILD ] += incrementBuild;
    return *this;
}

// Define prefix increment operator.
Version &Version::operator++()
{
    *this += 1;
    return *this;
}

// Define postfix increment operator.
Version Version::operator++( int incrementBuild )
{
    Version temp = *this;
    ++*this;
    return temp;
}
bool Version::operator==( const Version &rhs )
{
    return _version[ VERSION::MAJOR ] == rhs.getMajor() &&
           _version[ VERSION::MINOR ] == rhs.getMinor() &&
           _version[ VERSION::PATCH ] == rhs.getPatch() &&
           _version[ VERSION::BUILD ] == rhs.getBuild();
}
bool Version::operator>( const Version &rhs )
{
    return _version[ VERSION::MAJOR ] > rhs.getMajor() ||
           _version[ VERSION::MINOR ] > rhs.getMinor() ||
           _version[ VERSION::PATCH ] > rhs.getPatch() ||
           _version[ VERSION::BUILD ] > rhs.getBuild();
}
bool Version::operator<( const Version &rhs )
{
    return _version[ VERSION::MAJOR ] < rhs.getMajor() ||
           _version[ VERSION::MINOR ] < rhs.getMinor() ||
           _version[ VERSION::PATCH ] < rhs.getPatch() ||
           _version[ VERSION::BUILD ] < rhs.getBuild();
}
bool Version::operator!=( const Version &rhs )
{
    return !( *this == rhs );
}
bool Version::operator>=( const Version &rhs )
{
    return *this > rhs || *this == rhs;
}
bool Version::operator<=( const Version &rhs )
{
    return *this < rhs || *this == rhs;
}
Version::Version( const char *version )
{
    if( version == nullptr || version[ 0 ] == '\0' )
        return;

    set( version );
}

void Version::set( const char *version )
{
    if( version == nullptr || version[ 0 ] == '\0' )
        return;

    set( 0, 0, 0, 0 );

    int i = -1, c;
    unsigned long val = 0;
    unsigned short valLen = 0;
    VERSION select = MAJOR;

    c = version[ 0 ];
    while( c >= '0' && c <= '9' )
    {
        if( valLen > MAX_UINT_STRING_LEN )
        {
            set( 0, 0, 0, 0 );
            return; // number too long;
        }
        c = version[ ++i ];
        if( c < '0' || c > '9' )
        {

            _version[ select ] = val;
            select = ( VERSION ) ( ( int ) ( select ) + 1 );

            if( c == '\0' || i > MAX_VERSION_STRING_LEN )
                return;

            val = 0;
            valLen = 0;
            c = version[ ++i ];
        }
        val = val * 10 + ( c - 48 );
        valLen++;
    }
    if( c != '\0' )
    {
        set( 0, 0, 0, 0 );
        return; // invalid version;
    }
}

Version::Version( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build )
{
    set( major, minor, patch, build );
}

Version::~Version()
{
    delete[] m_versionFull;
}

const char *Version::itoa( unsigned int val, int base )
{

    static char buf[ 32 ] = { 0 };
    if( val == 0 )
    {
        buf[ 0 ] = '0';
        return buf;
    }
    else
    {
        int i = 30;

        for(; val && i; --i, val /= base )
            buf[ i ] = "0123456789abcdef"[ val % base ];
        return &buf[ i + 1 ];
    }
}

const char *Version::c_str()
{
    if( !m_versionFull )
    {
        m_versionFull = new char[ MAX_VERSION_STRING_LEN ];
    }
    m_versionFull[ 0 ] = '\0';

    unsigned int val, pos = -1;
    for( int ver = VERSION::MAJOR; ver <= VERSION::BUILD; ver++ )
    {
        val = _version[ ver ];

        const char *p = itoa( val, 10 );
        unsigned int i = 0;
        while( p[ i ] != '\0' )
        {
            m_versionFull[ ++pos ] = p[ i++ ];
        }
        if( ver < 3 )
        {
            m_versionFull[ ++pos ] = '.';
        }
    }
    m_versionFull[ ++pos ] = '\0';

    return m_versionFull;
}
void Version::set( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build )
{
    _version[ VERSION::MAJOR ] = major;
    _version[ VERSION::MINOR ] = minor;
    _version[ VERSION::PATCH ] = patch;
    _version[ VERSION::BUILD ] = build;
    if( m_versionFull )
        m_versionFull[ 0 ] = '\0';
}

void Version::setMajor( unsigned int value )
{
    set( value, _version[ 1 ], _version[ 2 ], _version[ 3 ] );
}

void Version::setMinor( unsigned int value )
{
    set( _version[ 0 ], value, _version[ 2 ], _version[ 3 ] );
}
void Version::setPatch( unsigned int value )
{
    set( _version[ 0 ], _version[ 1 ], value, _version[ 3 ] );
}
void Version::setBuild( unsigned int value )
{
    set( _version[ 0 ], _version[ 1 ], _version[ 2 ], value );
}

unsigned int Version::getMajor() const
{
    return _version[ VERSION::MAJOR ];
}
unsigned int Version::getMinor() const
{
    return _version[ VERSION::MINOR ];
}
unsigned int Version::getPatch() const
{
    return _version[ VERSION::PATCH ];
}
unsigned int Version::getBuild() const
{
    return _version[ VERSION::BUILD ];
}
