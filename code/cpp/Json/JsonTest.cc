
// File: MyGoogleTestProject.cc
#include <gtest/gtest.h>
#include <Json/Json.h>
#include <fstream>
// Demonstrate some basic assertions.
TEST( JsonTest, DefineJson )
{
    JsonG::Json json( "{\"hello\":\"world\"}" );
    JsonData *jd = json.getRootObject();
    EXPECT_TRUE( jd != NULL ) << "Json root object should have been created";
    EXPECT_STREQ( "{\"hello\":\"world\"}", json.toString().c_str() );
}

std::string fileToString( std::string filename )
{
    std::ifstream ifs( filename, std::ifstream::in );
    EXPECT_FALSE( ifs.fail() ) << "\n======================   INVALID TEST   ======================\n Unable to open file: \"" << filename <<
    "\".\n Did you forget to set ENABLE_TESTS to TRUE in CMakeLists.txt\n==============================================================\n\n";
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string str = buffer.str();
    return str;
}

JsonData *getRootObject( std::string filename )
{
    std::string str = fileToString( filename );
    JsonG::Json json( str.c_str() );
    EXPECT_TRUE( json.isValid() ) << "Invalid json file";
    if( !json.isValid() )
    {
        return NULL;
    }
    JsonData *jd = json.getRootObject();
    EXPECT_TRUE( jd != NULL && jd->isValid() ) << "Root object is null or invalid";
    if( jd == NULL || !jd->isValid() )
    {
        return NULL;
    }
    EXPECT_TRUE( jd->hasChildren() ) << "Error, Root object has no children!";
    return jd->hasChildren() ? jd : NULL;
}

TEST( JsonTest, LoadFile_testOne )
{
    std::string str = fileToString( "testData/testOne.json" );
    JsonG::Json json( str.c_str() );
    EXPECT_STREQ( "{\"One\":1}", json.toString().c_str() );
    // EXPECT_TRUE( 1 == 0 ) << "Krapp" << "\n" << str << std::endl;
    JsonData *jd = json.getRootObject();
    EXPECT_TRUE( jd != NULL ) << "Json root object should have been created";
    EXPECT_EQ( 1, jd->getChild( "One" )->getValueAsInt() ) << "One should have the value 1";
}

TEST( JsonTest, LoadFile_test )
{
    JsonData *jd = getRootObject( "testData/test.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example1 )
{
    JsonData *jd = getRootObject( "testData/example1.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example2 )
{
    JsonData *jd = getRootObject( "testData/example2.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example3 )
{
    JsonData *jd = getRootObject( "testData/example3.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example4 )
{
    JsonData *jd = getRootObject( "testData/example4.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example5 )
{
    JsonData *jd = getRootObject( "testData/example5.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example6 )
{
    JsonData *jd = getRootObject( "testData/example6.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example7 )
{
    JsonData *jd = getRootObject( "testData/example7.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_example8 )
{
    JsonData *jd = getRootObject( "testData/example8.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_examplePins )
{
    JsonData *jd = getRootObject( "testData/examplePins.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
TEST( JsonTest, LoadFile_exampleStatus )
{
    JsonData *jd = getRootObject( "testData/exampleStatus.json" );
    ASSERT_TRUE( jd != NULL ) << "Invalid Root object";
}
