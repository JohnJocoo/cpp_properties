#pragma once

#include "property_member_pointer_discoverer.hpp"
#include "inner_traits.hpp"

#include <type_traits>

namespace prop {
namespace detail {

template < typename Owner, typename Property >
PROP_DETAIL_EXTENDED_CONSTEXPR_33fe95a2 Owner* repairOwnerPointer( Property* property )
{
  static_assert( std::is_const< Owner >::value == std::is_const< Property >::value,
    "Both Owner and property must have equal const modifiers.");
  
  using CleanOwner = ::prop::detail::CleanType< Owner >;
  using CleanProperty = ::prop::detail::CleanType< Property >;
  
  auto property_member_pointer = discoverPropertyPointer< CleanOwner, CleanProperty >();
  auto offset = ((char*)(&(((CleanOwner*)(nullptr))->*property_member_pointer))) - ((char*)nullptr);
  return (Owner*)(((char*)property) - offset);
}

} // namespace detail
} // namespace prop
