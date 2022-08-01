
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



/**
 * @brief Loads a json files into a Json object and checks if it has children
 *
 * @param filename
 * @return On success: pointer to a JsonG::Json* object which will need to be deleted by the user.
 *         On Error: NULL is returned.
 */
JsonG::Json *loadJsonFile( std::string filename )
{
    JsonG::Json *pJson = new JsonG::Json( fileToString( filename ).c_str() );
    // JsonG::Json json( fileToString( filename ).c_str() );
    EXPECT_TRUE( pJson->isValid() ) << "Invalid json file";
    if( !pJson->isValid() )
    {
        delete pJson;
        return NULL;
    }
    JsonData *jd = pJson->getRootObject();
    EXPECT_TRUE( jd != NULL && jd->isValid() ) << "Root object is null or invalid";
    if( jd == NULL || !jd->isValid() )
    {
        delete pJson;
        return NULL;
    }
    EXPECT_TRUE( jd->hasChildren() ) << "Error, Root object has no children!";
    if( !jd->hasChildren() )
    {
        delete pJson;
        return NULL;
    }

    return pJson;
}

TEST( JsonTest, LoadFile_testOne )
{
    std::string str = fileToString( "testData/testOne.json" );
    JsonG::Json json( str.c_str() );
    EXPECT_STREQ( "{\"One\":1}", json.toString().c_str() );
    JsonData *jd = json.getRootObject();
    EXPECT_TRUE( jd != NULL ) << "Json root object should have been created";
    EXPECT_EQ( 1, jd->getChild( "One" )->getValueAsInt() ) << "One should have the value 1";
}

TEST( JsonTest, LoadFile_test )
{
    JsonG::Json *pJson = loadJsonFile( "testData/test.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Json file";
    JsonData *jd = pJson->getRootObject();
    delete pJson;
}
TEST( JsonTest, LoadFile_example1 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example1.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}


TEST( JsonTest, LoadFile_example2 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example2.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_example3 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example3.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_example4 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example4.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_example5_testingFloat )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example5.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    JsonG::Json json( fileToString( "testData/example5.json" ).c_str() );

    //Test if keyfloat == 5.2
    JsonData *jd = pJson->getRootObject()->getChild( "keyfloat" );
    ASSERT_TRUE( jd != NULL && jd->isValid() && jd->hasChildren() ) << "Key 'keyfloat' missing";
    ASSERT_EQ( jd->getValueAsFloat(),  ( float ) 5.2 );


    // Test if record[1].floatNumber == -55.23
    jd = pJson->getRootObject()->getChild( "records" );
    ASSERT_EQ( jd->getType(), JSONTYPE::JSONTYPE_KEY_VALUE ) << "records key should be a key";
    ASSERT_EQ( jd->getValueType(), JSONTYPE::JSONTYPE_ARRAY ) << "records value should be a Array";
    ASSERT_EQ( jd->hasChildren(), true ) << "Array should have children";
    JsonData *arrayObject = jd->getChildAt( 0 );
    ASSERT_TRUE( arrayObject != NULL && arrayObject->isValid() ) << "records array should exist";
    JsonData *secondArrayItem = arrayObject->getChildAt( 1 );
    ASSERT_TRUE( secondArrayItem != NULL && secondArrayItem->isValid() ) << "Second array item should exist";
    JsonData *jdFloatNum = secondArrayItem->getChild( "floatNumber" );
    ASSERT_TRUE( jdFloatNum != NULL ) << "key 'floatNumber' should exist";
    float fNum = jdFloatNum->getValueAsFloat();
    ASSERT_EQ( fNum, ( float ) -55.23 ) << "floatNumber does not have the correct value";

    // Test if record[1].negativefloatNumber == -0.23
    jdFloatNum = secondArrayItem->getChild( "negativefloatNumber" );
    ASSERT_TRUE( jdFloatNum != NULL ) << "key 'negativefloatNumber' should exist";
    fNum = jdFloatNum->getValueAsFloat();
    ASSERT_EQ( fNum, ( float ) -0.23 ) << "negativefloatNumber does not have the correct value";

    //Test mixed value types in the same array
    jd = pJson->getRootObject()->getChild( "arrayOfStuf" );
    ASSERT_EQ( jd->getType(), JSONTYPE::JSONTYPE_KEY_VALUE ) << "records key should be a key";
    ASSERT_EQ( jd->getValueType(), JSONTYPE::JSONTYPE_ARRAY ) << "records value should be a Array";
    ASSERT_EQ( jd->hasChildren(), true ) << "Array should have children";
    arrayObject = jd->getChildAt( 0 );
    ASSERT_TRUE( arrayObject != NULL && arrayObject->isValid() ) << "arrayOfStuf array should exist";
    JsonData *current = arrayObject->getChildAt( 0 );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "first Item should exist in arrayOfStuf";
    ASSERT_STREQ( "string1", current->getValueAsString().c_str() ) << "Item of arrayOfStuf has incorrect value";

    current = arrayObject->getChildAt( 1 );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "second Item should exist in arrayOfStuf";
    ASSERT_STREQ( "String2", current->getValueAsString().c_str() ) << "Item of arrayOfStuf has incorrect value";

    current = arrayObject->getChildAt( 2 );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "third Item should exist in arrayOfStuf";
    ASSERT_EQ( 123, current->getValueAsInt() ) << "Item of arrayOfStuf has incorrect value";

    current = arrayObject->getChildAt( 3 );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "fourth Item should exist in arrayOfStuf";
    ASSERT_EQ( 456, current->getValueAsInt() ) << "Item of arrayOfStuf has incorrect value";

    current = arrayObject->getChildAt( 4 );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "fifth Item should exist in arrayOfStuf";
    ASSERT_EQ( -789, current->getValueAsInt() ) << "Item of arrayOfStuf has incorrect value";

    current = arrayObject->getChildAt( 5 );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "sixth Item should exist in arrayOfStuf";
    ASSERT_TRUE( current->getValueType() == JSONTYPE::JSONTYPE_KEY_VALUE ) << "sixth Item value should be of type JSONTYPE_KEY_VALUE";
    current = current->getChild( "prufakey" );
    ASSERT_TRUE( current != NULL && current->isValid() ) << "sixth Item be a valid json key value pair";
    ASSERT_STREQ( "prufakeyvalue", current->getValueAsString().c_str() ) << "object of Item of arrayOfStuf has incorrect value";


    delete pJson;
}
TEST( JsonTest, LoadFile_example6 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example6.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_example7 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example7.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_example8 )
{
    JsonG::Json *pJson = loadJsonFile( "testData/example8.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_examplePins )
{
    JsonG::Json *pJson = loadJsonFile( "testData/examplePins.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;
}
TEST( JsonTest, LoadFile_exampleStatus )
{
    JsonG::Json *pJson = loadJsonFile( "testData/exampleStatus.json" );
    ASSERT_TRUE( pJson != NULL ) << "Invalid Root object";
    delete pJson;

}
