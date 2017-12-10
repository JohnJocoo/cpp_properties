#pragma once

#include <type_traits>

#include "../enable_properties.hpp"
#include "is_property.hpp"
#include "is_alias_property.hpp"

#define PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 \
"Property owner must inherit from ::prop::EnableProperties"

#define PROP_DETAIL_IS_RW_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 \
"Property value must be copy-assignable clean type"

#define PROP_DETAIL_IS_RO_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 \
"Property value must be clean type"

namespace prop {
namespace detail {

template< class T >
using CleanType = typename std::decay< T >::type;

template< typename Owner >
struct IsOwnerGood :
  std::integral_constant< bool,
    std::is_base_of< ::prop::EnableProperties, Owner >::value >
{
}; // struct IsOwnerGood

template< typename ValueType >
struct IsRWPropertyValueGood :
  std::integral_constant< bool,
    std::is_copy_assignable< ValueType >::value &&
    std::is_same< ValueType,
      ::prop::detail::CleanType< ValueType > >::value >
{
}; // struct IsRWPropertyValueGood

template< typename ValueType >
struct IsROPropertyValueGood :
  std::integral_constant< bool, std::is_same< ValueType,
      ::prop::detail::CleanType< ValueType > >::value >
{
}; // struct IsROPropertyValueGood

} // namespace detail
} // namespace prop
