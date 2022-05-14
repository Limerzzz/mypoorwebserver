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

   set_target_properties( ${lime_example_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        COMMAND ${lime_example_name}
   )
endforeach(lime_example_source ${LIME_EXAMPLE_SOURCE} )