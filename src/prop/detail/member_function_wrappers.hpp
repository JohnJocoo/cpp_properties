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
  using CleanReturnType = ::prop::detail::CleanType< ReturnType >::type;
  using FunctionType = ReturnType( Class::* )() const;

  static constexpr FunctionType pointer()
  {
    return MemberGet;
  }

}; // struct GetterWrapper

template < typename Class_, typename ArgType,
  void ( Class_::*MemberSet )( ArgType ) >
struct SetterWrapper
{
  using Class = Class_;
  using ArgumentType = ArgType;
  using CleanArgumentType = ::prop::detail::CleanType< ArgumentType >::type;
  using FunctionType = void ( Class::* )( ArgumentType );

  static constexpr FunctionType pointer()
  {
    return MemberSet;
  }

}; // struct SetterWrapper

template < typename Class, typename ReturnType >
Identity< ReturnType > getReturnType( ReturnType( Class::* )() const )
{
  return {};
}

template < typename Class, typename ArgumentType >
Identity< ArgumentType > getArgumentType( void ( Class::* )( ArgumentType ) )
{
  return {};
}

} // namespace detail
} // namespace prop
