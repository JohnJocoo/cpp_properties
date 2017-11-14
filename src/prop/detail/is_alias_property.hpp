#pragma once

#include <type_traits>

#include "forward_declarations.hpp"

namespace prop {
namespace detail {

template < typename T >
struct IsAliasProperty : std::integral_constant< bool, false >
{
}; // struct IsAliasProperty< T >

template < typename OwnerType, typename PropType,
  PropType OwnerType::*Property, std::size_t Index,
  typename AccessorTag >
struct IsAliasProperty < ::prop::AliasProperty< OwnerType, PropType,
  Property, Index, AccessorTag > > : std::integral_constant< bool, true >
{
}; // struct IsAliasProperty< AliasProperty >

} // namespace detail
} // namespace prop
