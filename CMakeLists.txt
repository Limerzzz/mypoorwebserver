cmake_minimum_required(VERSION 3.10)
# generate  a JSON compile database one has to select a
# generator that support it.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# If present and true, this will cause all libraries to 
# be built shared unless the library was explicitly added as a static library.
set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(Lime
        VERSION 0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#include
set(LIME_SRC_INCLUDE_DIR ${PROJECT_BINARY_DIR}/src/include)
# set(LIME_EXAMPLE_INCLUDE_DIR ${PROJECT_BINARY_DIR}/example/include)
include_directories(${LIME_SRC_INCLUDE_DIR} ${LIME_EXAMPLE_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(example)

