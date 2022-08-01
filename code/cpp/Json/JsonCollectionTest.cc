
// File: MyGoogleTestProject.cc
#include <gtest/gtest.h>
#include <Json/Json.h>
#include <Json/Person.cpp>
#include "Json/JsonFile.h"
#include <Json/JsonFileCollection.h>
#include <filesystem>
#include <fstream>


// // Demonstrate some basic assertions.
// std::string fileToString2( std::string filename )
// {
//     std::ifstream ifs( filename, std::ifstream::in );
//     EXPECT_FALSE( ifs.fail() ) << "\n======================   INVALID TEST   ======================\n Unable to open file: \"" << filename <<
//     "\".\n Did you forget to set ENABLE_TESTS to TRUE in CMakeLists.txt\n==============================================================\n\n";
//     std::stringstream buffer;
//     buffer << ifs.rdbuf();
//     std::string str = buffer.str();
//     return str;
// }

void deleteFile( std::string fileName )
{
    std::ifstream infile( fileName );

    if( infile.good() )
    {
        infile.close();
        std::remove( fileName.c_str() );
    }
}

TEST( JsonCollectionTest, SetAndGetPersonColl )
{
    JsonFileCollection< Person > coll;
    EXPECT_EQ( coll.count(), 0 );
    String orgJsonStr="[{\"name\":\"Gudjon\",\"age\":51},{\"name\":\"Orri\",\"age\":12}]";
    EXPECT_TRUE( coll.setFromJson( orgJsonStr.c_str() ) );
    EXPECT_EQ( coll.count(), 2 );
    String actualStr=coll.toJsonString();
    EXPECT_STREQ( actualStr.c_str(), orgJsonStr.c_str() );
}

TEST( JsonCollectionTest, SaveAndLoadPersonColl )
{
    std::string fileName="coll-person.json";
    deleteFile( fileName );

    JsonFileCollection< Person > coll;
    EXPECT_EQ( coll.count(), 0 ) << "Collection count should be zero";
    String orgJsonStr="[{\"name\":\"Gudjon\",\"age\":51},{\"name\":\"Orri\",\"age\":12}]";
    EXPECT_TRUE( coll.setFromJson( orgJsonStr.c_str() ) );
    EXPECT_EQ( coll.count(), 2 ) << "Collection count should be 2";
    coll.setFilename( fileName );
    EXPECT_TRUE( coll.save() );

    JsonFileCollection< Person > coll2( fileName );
    EXPECT_EQ( coll2.count(), 0 );
    EXPECT_TRUE( coll2.load() );
    EXPECT_EQ( coll.count(), 2 );
    Person p;
    ASSERT_TRUE( coll.getFirstItem( &p ) );
    EXPECT_EQ( 51, p._age );
    EXPECT_STREQ( "Gudjon", p._name.c_str() );
    ASSERT_TRUE( coll.getNextItem( &p ) );
    EXPECT_STREQ( "Orri", p._name.c_str() );
    EXPECT_EQ( 12, p._age );

}


