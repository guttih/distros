
// File: MyGoogleTestProject.cc
#include <gtest/gtest.h>
#include <Json/Version.h>
// Demonstrate some basic assertions.
TEST( VersionTest, constructor_string )
{

    Version ver( "1.20.300.4000" );
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 20 );
    EXPECT_EQ( ver.getPatch(), 300 );
    EXPECT_EQ( ver.getBuild(), 4000 );
}

TEST( VersionTest, incrementNumber10 ) {
    Version ver( "1.2.3.4" );
    ver+=6;
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 2 );
    EXPECT_EQ( ver.getPatch(), 3 );
    EXPECT_EQ( ver.getBuild(), 10 );
}

TEST( VersionTest, postfixIncrement ) {
    Version ver( "1" );
    ver++;
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 0 );
    EXPECT_EQ( ver.getPatch(), 0 );
    EXPECT_EQ( ver.getBuild(), 1 );
    Version ver2 = ver;
    EXPECT_TRUE( ver == ver2 );
    EXPECT_TRUE( ver++ == ver2 );
    EXPECT_FALSE( ver == ver2 );
    EXPECT_EQ( ver.getBuild(), 2 );
}



TEST( VersionTest, prefixIncrement ) {
    Version ver( "1" );
    ++ver;
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 0 );
    EXPECT_EQ( ver.getPatch(), 0 );
    EXPECT_EQ( ver.getBuild(), 1 );

    Version ver2 = ver;
    EXPECT_TRUE( ver == ver2 );
    EXPECT_FALSE( ++ver == ver2 );
    EXPECT_EQ( ver.getBuild(), 2 );
}

TEST( VersionTest, IncrementMajor ) {
    Version ver( "1.1.1.1" );
    ver.IncrementMajor();
    EXPECT_EQ( ver.getMajor(), 2 );
    EXPECT_EQ( ver.getMinor(), 0 );
    EXPECT_EQ( ver.getPatch(), 0 );
    EXPECT_EQ( ver.getBuild(), 0 );
}

TEST( VersionTest, IncrementMinor ) {
    Version ver( "1.1.1.1" );
    ver.IncrementMinor();
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 2 );
    EXPECT_EQ( ver.getPatch(), 0 );
    EXPECT_EQ( ver.getBuild(), 0 );
}

TEST( VersionTest, IncrementPatch ) {
    Version ver( "1.1.1.1" );
    ver.IncrementPatch();
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 1 );
    EXPECT_EQ( ver.getPatch(), 2 );
    EXPECT_EQ( ver.getBuild(), 0 );
}

TEST( VersionTest, IncrementBuild ) {
    Version ver( "1.1.1.1" );
    ver.IncrementBuild();
    EXPECT_EQ( ver.getMajor(), 1 );
    EXPECT_EQ( ver.getMinor(), 1 );
    EXPECT_EQ( ver.getPatch(), 1 );
    EXPECT_EQ( ver.getBuild(), 2 );
}

