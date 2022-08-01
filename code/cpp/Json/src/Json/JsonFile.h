#ifndef JsonFile_H
#define JsonFile_H
#include <fstream>

template< typename T >
class JsonFile : public T
{
private:
    std::string _filename;

public:
    JsonFile()
    {
    };

    void setFilename( std::string filename )
    {
        _filename = filename;
    };

    std::string getFilename()
    {
        return _filename;
    }

    bool save( const char *filename = NULL )
    {
        std::string fName = filename ? filename : this->getFilename();
        FILE *fp;
        fp = fopen( fName.c_str(), "w" );
        if( !fp )
            return false;
        int cnt = fprintf( fp, "%s ", this->toJsonString().c_str() );
        fclose( fp );
        return cnt > 0;
    }

    std::string fileToString( const char *fileName )
    {

        std::ifstream ifs( fileName, std::ifstream::in );
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        std::string str = buffer.str();
        return str;
    }

    bool load( const char *filename = NULL )
    {
        std::string fName = filename ? filename : this->getFilename();
        return this->setFromJson( this->fileToString( fName.c_str() ).c_str() );
    }
};

#endif
