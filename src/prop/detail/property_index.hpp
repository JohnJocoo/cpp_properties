#pragma once

#include <type_traits>
#include <cstddef>

#include "forward_declarations.hpp"

namespace prop {
namespace detail {

template < typename T >
struct PropertyIndex
{
}; // struct PropertyIndex

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner, typename AccessorTag >
struct PropertyIndex< HoldingProperty< OwnerType, ValType,
    IndexInOwner, AccessorTag > > :
  public std::integral_constant< std::size_t, IndexInOwner >
{
}; // struct PropertyIndex< HoldingProperty >

template < typename OwnerType, typename ValType,
  ValType OwnerType::*Member, std::size_t IndexInOwner,
  typename AccessorTag >
struct PropertyIndex< MemberProperty< OwnerType, ValType,
    Member, IndexInOwner, AccessorTag > > :
  public std::integral_constant< std::size_t, IndexInOwner >
{
}; // struct PropertyIndex< MemberProperty >

template < typename OwnerType, typename ValType,
  typename ReadF, typename WriteFOrTag, std::size_t IndexInOwner,
  typename TagOrVoid >
struct PropertyIndex< MethodProperty< OwnerType, ValType,
    ReadF, WriteFOrTag, IndexInOwner, TagOrVoid > > :
  public std::integral_constant< std::size_t, IndexInOwner >
{
}; // struct PropertyIndex< MethodProperty >

template < typename OwnerType, typename PropType,
  PropType OwnerType::*Property, std::size_t IndexInOwner,
  typename AccessorTag >
struct PropertyIndex< AliasProperty< OwnerType, PropType,
    Property, IndexInOwner, AccessorTag > > :
  public std::integral_constant< std::size_t, IndexInOwner >
{
}; // struct PropertyIndex< AliasProperty >

} // namespace detail
} // namespace prop
