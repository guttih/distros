#ifndef JsonFileCollection_H
#define JsonFileCollection_H
#include <vector>


template< typename T >
class JsonFileCollection : public JsonFile< T >
{
private:

public:
    JsonFileCollection()
    {
    };
    JsonFileCollection( std::string filename )
    {
        this->setFilename( filename );
    };

    ~JsonFileCollection()
    {
    };

    void addItem( T const item )
    {
        _list.push_back( item );
    }
    void print()
    {
        typename std::vector< T >::const_iterator it;
        it=_list.begin();
        int i = 0;
        while( it != _list.end() )
        {
            printf( "%d: %s\n", ++i, ( *it ).toJsonString().c_str() );
            ++it;
        }
    }

    String toJsonString() const
    {
        String ss="[";
        for( typename std::vector< T >::const_iterator it=_list.begin(); it != _list.end(); it++ )
        {
            ss+= ( *it ).toJsonString();
            if( next( it ) != _list.end() )
            {
                ss+= ",";
            }
        }
        ss+= "]";
        return ss;
    };

    bool setFromJson( const char *jsonString )
    {
        JsonG::Json json( jsonString );

        if( !json.isValid() )
            return false;

        JsonData *root=json.getRootObject();
        if( !root || root->getType() != JSONTYPE::JSONTYPE_ARRAY )
            return false;

        JsonData *child;
        T tmp;
        child=root->getChildAt( 0 );
        _list.clear();
        do
        {
            if( !T::getValues( child, &tmp ) )
                return false;

            _list.push_back( tmp );

            child=child->getNext();

        } while( child );

        return true;
    }

    unsigned int count()
    {
        return _list.size();
    }

    void clear()
    {
        return _list.clear();
    }
    bool RemoveItem( T const item )
    {
        T x( item );
        String jsonStringToMatch = x.toJsonString();
        for( typename std::vector< T >::iterator it=_list.begin(); it != _list.end(); it++ )
        {

            if( ( *it ).toJsonString() == jsonStringToMatch )
            {
                _list.erase( it );
                return true;
            }
        }
        return false;
    }

    bool getFirstItem( T *item )
    {
        _itStepping=_list.begin();
        if( _itStepping != _list.end() )
        {
            return item->setFromJson( ( *_itStepping ).toJsonString().c_str() );
        }
        return false;
    }
    bool getNextItem( T *item )
    {
        ++_itStepping;
        if( _itStepping != _list.end() )
        {
            std::string str=( *_itStepping ).toJsonString().c_str();
            return item->setFromJson( str.c_str() );
        }
        return false;
    }


private:
    typename std::vector< T > _list;
    typename std::vector< T >::const_iterator _itStepping;
};


// template< typename T >
// JsonFileCollection::~JsonFileCollection()
// {
//     _list.clear();

// }



#endif
