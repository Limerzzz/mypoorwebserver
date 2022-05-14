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


#generate binary file
file(GLOB LIME_EXAMPLE_SOURCE "${PROJECT_SOURCE_DIR}/example/*.cpp")
foreach(lime_example_source ${LIME_EXAMPLE_SOURCE} )
   # extra the filename without the path
   get_filename_component(lime_example_filename ${lime_example_source} NAME)
   # delete the file name extension(such as .cpp)
   string(REPLACE ".cpp" "" lime_example_name ${lime_example_filename})
   # build bin file 
   add_executable(${lime_example_name} ${lime_example_source})
   target_link_libraries(${lime_example_name} lime_shared)
   target_include_directories(${lime_example_name} 
        PRIVATE
        ${LIME_SRC_INCLUDE_DIR})
   set_target_properties( ${lime_example_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        COMMAND ${lime_example_name}
   )
endforeach(lime_example_source ${LIME_EXAMPLE_SOURCE} )

