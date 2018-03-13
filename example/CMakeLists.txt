cmake_minimum_required( VERSION 3.7 )

project( EXAMPLES LANGUAGES CXX )

set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )
                
add_executable( example_my_url "${SRC_DIR}/my_url.cpp" )

target_link_libraries( example_my_url cpp_properties )
