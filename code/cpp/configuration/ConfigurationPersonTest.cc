
// File: MyGoogleTestProject.cc
#include <gtest/gtest.h>
#include "src/Person.cpp"
// Demonstrate some basic assertions.

TEST( ConfigurationPersonTest, Person_SetAndGet )
{
    Person p;
    p.set( "gudjon", 50 );
    EXPECT_STREQ( "gudjon", p._name.c_str() );
    EXPECT_EQ( p._age, 50 );
}
TEST( ConfigurationPersonTest, Person_setFromJson )
{
    Person p( "before", 1 );
    p.setFromJson( "{\"name\":\"gudjon\",\"age\":50}" );
    EXPECT_STREQ( "gudjon", p._name.c_str() );
    EXPECT_EQ( p._age, 50 );
}
TEST( ConfigurationPersonTest, Person_toJsonString )
{
    Person p( "before", 1 );
    p.setFromJson( "{\"name\":\"gudjon\",\"age\":50}" );
    EXPECT_STREQ( "{\"name\":\"gudjon\",\"age\":50}", p.toJsonString().c_str() );
    EXPECT_EQ( p._age, 50 );
}
