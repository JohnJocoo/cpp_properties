#pragma once

#include <type_traits>

#include "../enable_properties.hpp"
#include "is_property.hpp"
#include "is_alias_property.hpp"

namespace prop {
namespace detail {

template< class T >
using CleanType = typename std::decay< T >::type;

template< typename Owner >
struct IsOwnerGood :
  std::integral_constant< bool,
    std::is_base_of< ::prop::EnableProperties, T >::value >
{
  static constexpr const char* ErrorMessage = "Property owner must inherit from ::prop::EnableProperties";
  
}; // struct IsOwnerGood

template< typename ValueType >
struct IsPropertyValueGood :
  std::integral_constant< bool,
    std::is_copy_assignable< ValueType >::value &&
    std::is_same< ValueType, ::prop::detail::CleanType< ValueType > > >
{
  static constexpr const char* ErrorMessage = "Property value must be copy-assignable clean type";
  
}; // struct IsPropertyValueGood

} // namespace detail
} // namespace prop
