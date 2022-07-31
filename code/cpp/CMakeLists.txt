cmake_minimum_required(VERSION 3.2)
set(This rhatdist)
project(${This} VERSION 1.0.0)


add_subdirectory(Json)
add_subdirectory(configuration)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( ${This} ${This}.cc )
target_link_libraries( ${This} gtest_main )

include(GoogleTest)
gtest_discover_tests(${This})

# See tutorial to update the url in FetchContent to latest release of googletest
# Tutorial: https://github.com/google/googletest/blob/main/docs/quickstart-cmake.md

