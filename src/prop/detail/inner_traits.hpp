#pragma once

#include <type_traits>

#include "enable_properties.hpp"
#include "is_property.hpp"
#include "is_alias_property.hpp"
#include "property_index.hpp"

#define PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 \
"Property owner must inherit from ::prop::EnableProperties"

#define PROP_DETAIL_IS_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 \
"Property value must be copy-constructable & copy-assignable clean type"

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
struct IsPropertyValueGood :
  std::integral_constant< bool,
    std::is_copy_assignable< ValueType >::value &&
    std::is_copy_constructible< ValueType >::value &&
    std::is_same< ValueType,
      ::prop::detail::CleanType< ValueType > >::value >
{
}; // struct IsPropertyValueGood

} // namespace detail
} // namespace prop
