#pragma once

#include <type_traits>

#include "forward_declarations.hpp"

namespace prop {
namespace detail {

template < typename T >
struct IsProperty : std::integral_constant< bool, false >
{
}; // struct IsProperty< T >

template < typename OwnerType, typename ValType,
  std::size_t Index, typename AccessorTag >
struct IsProperty < ::prop::HoldingProperty< OwnerType, ValType,
  Index, AccessorTag > > : std::integral_constant< bool, true >
{
}; // struct IsProperty< HoldingProperty >

template < typename OwnerType, typename ValType,
  ValType OwnerType::*Member, std::size_t Index, typename AccessorTag >
struct IsProperty < ::prop::MemberProperty< OwnerType, ValType,
  Member, Index, AccessorTag > > : std::integral_constant< bool, true >
{
}; // struct IsProperty< MemberProperty >

template < typename OwnerType, typename ValType,
  typename ReadF, typename WriteFOrTag, std::size_t Index,
  typename TagOrVoid >
class MethodProperty
struct IsProperty < ::prop::MethodProperty< OwnerType, ValType,
  ReadF, WriteFOrTag, Index, TagOrVoid > > : std::integral_constant< bool, true >
{
}; // struct IsProperty< MethodProperty >

template < typename OwnerType, typename PropType,
  PropType OwnerType::*Property, std::size_t Index,
  typename AccessorTag >
struct IsProperty < ::prop::AliasProperty< OwnerType, PropType,
  Property, Index, AccessorTag > > : std::integral_constant< bool, true >
{
}; // struct IsProperty< AliasProperty >

} // namespace detail
} // namespace prop
