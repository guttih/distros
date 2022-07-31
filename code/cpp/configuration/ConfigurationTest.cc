
// File: MyGoogleTestProject.cc
#include <gtest/gtest.h>
// Demonstrate some basic assertions.
TEST( ConfigurationTest, BasicAssertions )
{
    // Expect two strings not to be equal.
    EXPECT_STRNE( "hellox", "worldx" );
    // Expect equality.
    EXPECT_EQ( 7 * 6, 42 );
}


// 2. Run these commands
//     cmake -S . -B build
//     cmake --build build

// See tutorial to update the url in FetchContent to latest release of googletest
// Tutorial: https://github.com/google/googletest/blob/main/docs/quickstart-cmake.md