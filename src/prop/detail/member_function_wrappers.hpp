#pragma once

#include "inner_traits.hpp"
#include "identity.hpp"

namespace prop {
namespace detail {

template < typename Class_, typename RetType,
  RetType( Class_::*MemberGet )() const >
struct GetterWrapper
{
  using Class = Class_;
  using ReturnType = RetType;
  using CleanReturnType = typename ::prop::detail::CleanType< ReturnType >;
  using FunctionType = ReturnType( Class::* )() const;
  
  static constexpr FunctionType Pointer = MemberGet;

}; // struct GetterWrapper

template < typename Class_, typename ArgType,
  void ( Class_::*MemberSet )( ArgType ) >
struct SetterWrapper
{
  using Class = Class_;
  using ArgumentType = ArgType;
  using CleanArgumentType = typename ::prop::detail::CleanType< ArgumentType >;
  using FunctionType = void ( Class::* )( ArgumentType );

  static constexpr FunctionType Pointer = MemberSet;

}; // struct SetterWrapper

template < typename Class, typename ReturnType >
constexpr Identity< ReturnType > getReturnType( ReturnType( Class::* )() const )
{
  return {};
}

template < typename Class, typename ArgumentType >
constexpr Identity< ArgumentType > getArgumentType( void ( Class::* )( ArgumentType ) )
{
  return {};
}

} // namespace detail
} // namespace prop
