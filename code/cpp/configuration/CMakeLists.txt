
project(Configuration)
include_directories(src)

# message(STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxTEST")
message(STATUS "CMAKE_CURRENT_BINARY_DIR>>>>: ${CMAKE_CURRENT_BINARY_DIR}")
add_executable(configuration main.cpp)
target_link_libraries(configuration PUBLIC Json)

# Adding google tests
enable_testing()
add_executable( 
    ConfigurationTest 
    ConfigurationTest.cc 
    ConfigurationPersonTest.cc
    )
target_link_libraries(ConfigurationTest gtest_main Json)
include(GoogleTest)
gtest_discover_tests(ConfigurationTest)

