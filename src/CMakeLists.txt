cmake_minimum_required( VERSION 3.7 )

project( CPP_PROPERTIES LANGUAGES CXX )

set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )
set( LIB_SOURCES "${SRC_DIR}/prop/alias_property.hpp"
                 "${SRC_DIR}/prop/holding_property.hpp"
                 "${SRC_DIR}/prop/member_property.hpp"
                 "${SRC_DIR}/prop/method_property.hpp"
                 "${SRC_DIR}/prop/properties.hpp"
                 "${SRC_DIR}/prop/property_tags.hpp"
                 "${SRC_DIR}/prop/enable_properties.hpp"
                 "${SRC_DIR}/prop/detail/alias_property.hpp"
                 "${SRC_DIR}/prop/detail/holding_property.hpp"
                 "${SRC_DIR}/prop/detail/member_property.hpp"
                 "${SRC_DIR}/prop/detail/method_property.hpp"
                 "${SRC_DIR}/prop/detail/property_tags.hpp"
                 "${SRC_DIR}/prop/detail/enable_properties.hpp"
                 "${SRC_DIR}/prop/detail/forward_declarations.hpp"
                 "${SRC_DIR}/prop/detail/index.hpp"
                 "${SRC_DIR}/prop/detail/property_base.hpp"
                 "${SRC_DIR}/prop/detail/property_real_value_base.hpp"
                 "${SRC_DIR}/prop/detail/static_class_counter.hpp"
                 "${SRC_DIR}/prop/detail/inner_traits.hpp"
                 "${SRC_DIR}/prop/detail/unwrap_if_property.hpp"
                 "${SRC_DIR}/prop/detail/member_function_wrappers.hpp"
                 "${SRC_DIR}/prop/detail/identity.hpp"
                 "${SRC_DIR}/prop/detail/setter_argument_mutator.hpp"
                 "${SRC_DIR}/prop/detail/is_property.hpp"
                 "${SRC_DIR}/prop/detail/is_alias_property.hpp"
                 "${SRC_DIR}/prop/detail/property_real_value_visitor.hpp" 
                 "${SRC_DIR}/prop/detail/property_holding_base.hpp"
                 "${SRC_DIR}/prop/detail/property_method_base.hpp"
                 "${SRC_DIR}/prop/detail/property_info.hpp"
                 "${SRC_DIR}/prop/detail/owner_pointer_reparator.hpp"
                 "${SRC_DIR}/prop/detail/property_member_pointer_discoverer.hpp"
                 "${SRC_DIR}/prop/detail/property_index.hpp"
                 "${SRC_DIR}/prop/detail/property_operators_common.hpp"
                 "${SRC_DIR}/prop/detail/property_base_visitor.hpp"
                 )
                
add_library( cpp_properties INTERFACE )
target_include_directories( cpp_properties INTERFACE 
                            "${SRC_DIR}/"
                            )
                            
add_custom_target( cpp_properties_header SOURCES ${LIB_SOURCES} )
