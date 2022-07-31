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

target_include_directories(Json PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_definitions(Json PUBLIC JSON_VERSION=1)