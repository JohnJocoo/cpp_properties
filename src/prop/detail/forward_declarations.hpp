#pragma once

#include <cstddef>

namespace prop {

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner, typename AccessorTag >
class HoldingProperty
{
public:
  static constexpr bool ErrorInDeclaration = true;
  
}; // class HoldingProperty

template < typename OwnerType, typename ValType,
  ValType OwnerType::*Member, std::size_t IndexInOwner, typename AccessorTag >
class MemberProperty
{
public:
  static constexpr bool ErrorInDeclaration = true;
  
}; // class MemberProperty

template < typename OwnerType, typename ValType,
  typename ReadF, typename WriteFOrTag, std::size_t IndexInOwner,
  typename TagOrVoid = void >
class MethodProperty
{
public:
  static constexpr bool ErrorInDeclaration = true;
  
}; // class MethodProperty

template < typename OwnerType, typename PropType,
  PropType OwnerType::*Property, std::size_t IndexInOwner,
  typename AccessorTag >
class AliasProperty
{
public:
  static constexpr bool ErrorInDeclaration = true;
  
}; // class AliasProperty

} // namespace prop
