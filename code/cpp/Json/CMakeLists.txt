# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake#answer-45843676

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
)

set(ENABLE_TESTS TRUE)

target_include_directories(Json PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_definitions(Json PUBLIC JSON_VERSION=1)

# Adding google tests
# include_directories(${CMAKE_CURRENT_BINARY_DIR}/testData)
if(${ENABLE_TESTS})
    enable_testing()
    #    add_subdirectory(testData)
    file(COPY testData DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

add_executable(
    JsonTest
    JsonTest.cc
)

# WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
target_link_libraries(JsonTest gtest_main Json)
include(GoogleTest)
gtest_discover_tests(JsonTest)