# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake#answer-45843676

project(JsonG VERSION 0.4.2.0)

add_library(
    Json
    src/Json/String.h
    src/Json/String.cpp
    src/Json/Json.h
    src/Json/Json.cpp
    src/Json/JsonData.cpp
    src/Json/JsonData.h
    src/Json/AbstractJsonFileData.h
    src/Json/AbstractJsonFileData.cpp
    src/Json/IJsonFileData.h
    src/Json/JsonFileCollection.h
    src/Json/JsonFile.h
    src/Json/NotImplementedException.h
    src/Json/Version.h
    src/Json/Version.cpp
)

set(ENABLE_TESTS TRUE)

target_include_directories(Json PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_definitions(Json PUBLIC JSON_VERSION=1)

# Adding google tests
if(${ENABLE_TESTS})
    enable_testing()
    file(COPY testData DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

configure_file(JsonGConfig.h.in JsonGConfig.h)

add_executable(
    JsonTest
    JsonTest.cc
    JsonCollectionTest.cc
    VersionTest.cc
)

target_link_libraries(JsonTest gtest_main Json)
include(GoogleTest)
gtest_discover_tests(JsonTest)