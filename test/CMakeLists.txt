cmake_minimum_required( VERSION 3.7 )

project( CPP_PROPERTIES_TEST LANGUAGES CXX )

include( gtest.cmake )

enable_testing()

set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )
set( TEST_SOURCES "${SRC_DIR}/common.hpp"
                  "${SRC_DIR}/holding_property.cpp"
                  "${SRC_DIR}/method_property.cpp"
                 )
                
add_executable( cpp_properties_test "${TEST_SOURCES}" )
target_link_libraries( cpp_properties_test cpp_properties libgtest libgtest_main )
