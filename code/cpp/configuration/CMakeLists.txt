
project(Configuration VERSION 0.1.0.0)
include_directories(src)
message(STATUS "CMAKE_CURRENT_BINARY_DIR>>>>: ${CMAKE_CURRENT_BINARY_DIR}")
configure_file(ConfigurationConfig.h.in ConfigurationConfig.h)
add_executable(configuration main.cpp )
target_link_libraries(configuration PUBLIC Json)
target_include_directories(configuration PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/Json"
                           )


install(TARGETS configuration DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/ConfigurationConfig.h"
  DESTINATION include
  )

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

# WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}