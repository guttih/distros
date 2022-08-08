
#ifndef VERSION_H
#define VERSION_H

#define MAX_UINT_STRING_LEN 20
#define MAX_VERSION_STRING_LEN ( 4 * MAX_UINT_STRING_LEN ) + 3 + 1

enum VERSION
{
    MAJOR = 0,
    MINOR,
    PATCH,
    BUILD
};

class Version
{
private:
    unsigned int _version[ 4 ] = { 0, 0, 0, 0 };
    char *m_versionFull = nullptr;
    const char *itoa( unsigned int val, int base );

public:
    // operators
    Version &operator=( const Version &rhs );
    Version &operator++();        // Prefix increment operator.
    Version operator++( int incrementBuild );// Postfix increment operator.
    Version &operator+=( const int &incrementBuild );
    bool operator==( const Version &rhs );
    bool operator>( const Version &rhs );
    bool operator<( const Version &rhs );
    bool operator!=( const Version &rhs );
    bool operator>=( const Version &rhs );
    bool operator<=( const Version &rhs );

    const char *c_str();
    Version( const char *version );
    Version( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build );
    void set( const char *value );
    void set( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build );
    void setMajor( unsigned int major );
    void setMinor( unsigned int minor );
    void setPatch( unsigned int patch );
    void setBuild( unsigned int build );
    unsigned int getMajor() const;
    unsigned int getMinor() const;
    unsigned int getPatch() const;
    unsigned int getBuild() const;
    bool isValid()
    {
        return _version[ VERSION::MAJOR ] > 0 ||
               _version[ VERSION::MINOR ] > 0 ||
               _version[ VERSION::PATCH ] > 0 ||
               _version[ VERSION::BUILD ] > 0;
    }

    ~Version();
};

#endif