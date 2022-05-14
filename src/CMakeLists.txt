#build library
# file(GLOB_RECURSE lime_source ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE lime_source ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
find_package(Threads)

add_library(lime_shared  SHARED ${lime_source})
target_include_directories(lime_shared
        PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(lime_shared ${CMAKE_THREAD_LIBS_INIT})