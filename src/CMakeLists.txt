cmake_minimum_required( VERSION 3.7 )

project(CPP_PROPERTIES LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )
set( LIB_SOURCES "${SRC_DIR}/prop/alias_property.hpp"
                 "${SRC_DIR}/prop/holding_property.hpp"
                 "${SRC_DIR}/prop/member_property.hpp"
                 "${SRC_DIR}/prop/method_property.hpp"
                 "${SRC_DIR}/prop/properties.hpp"
                 "${SRC_DIR}/prop/property_tags.hpp"
                 "${SRC_DIR}/prop/enable_properties.hpp"
                 "${SRC_DIR}/prop/detail/forward_declarations.hpp"
                 "${SRC_DIR}/prop/detail/index.hpp"
                 "${SRC_DIR}/prop/detail/property_base.hpp"
                 "${SRC_DIR}/prop/detail/static_class_counter.hpp"
                 "${SRC_DIR}/prop/detail/inner_traits.hpp"
                 )
                
add_library( cpp_properties INTERFACE )
target_include_directories( cpp_properties INTERFACE 
                            "${SRC_DIR}/prop"
                            "${SRC_DIR}/prop/detail" 
                            )
                            
add_custom_target( cpp_properties_header SOURCES ${LIB_SOURCES} )
