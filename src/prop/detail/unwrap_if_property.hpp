#pragma once

#include <type_traits>

#include "forward_declarations.hpp"
#include "../property_tags.hpp"

namespace prop {
namespace detail {

template < typename T >
struct UnwrapIfProperty // common case (not a property)
{
  using Type = T;

  static const Type& forward( const Type& value ) noexcept
  {
    return value;
  }

  static Type&& forward( Type&& value ) noexcept
  {
    return std::move( value );
  }
  
}; // struct UnwrapIfProperty< T > (common case)

template < typename Owner, typename ValType, std::size_t Index >
struct UnwrapIfProperty< ::prop::HoldingProperty< Owner,
  ValType, Index, ::prop::ReadWrite > >
  // read-write HoldingProperty - allow move from
{
  using Type = ValType;
  using Property = typename ::prop::HoldingProperty< Owner,
    ValType, Index, ::prop::ReadWrite >;

  static const Type& forward( const Property& value ) noexcept
  {
    return value.cref();
  }

  static Type&& forward( Property&& value ) noexcept
  {
    return std::move( value.ref() );
  }

}; // struct UnwrapIfProperty< HoldingProperty< ReadWrite > >

template < typename Owner, typename ValType, std::size_t Index >
struct UnwrapIfProperty< ::prop::HoldingProperty< Owner,
  ValType, Index, ::prop::ReadOnly > >
  // read-only HoldingProperty
{
  using Type = ValType;
  using Property = typename ::prop::HoldingProperty< Owner,
    ValType, Index, ::prop::ReadOnly >;
  
  static const Type& forward( const Property& value ) noexcept
  {
    return value.cref();
  }

}; // struct UnwrapIfProperty< HoldingProperty< ReadOnly > >

template < typename Owner, typename ValType,
  ValType Owner::*Member, std::size_t Index >
struct UnwrapIfProperty< ::prop::MemberProperty< Owner, ValType,
  Member, Index, ::prop::ReadWrite > >
  // read-write MemberProperty - allow move from
{
  using Type = ValType;
  using Property = ::prop::MemberProperty< Owner, ValType,
    Member, Index, ::prop::ReadWrite >;

  static const Type& forward( const Property& value ) noexcept
  {
    return value.cref();
  }

  static Type&& forward( Property&& value ) noexcept
  {
    return std::move( value.ref() );
  }
  
}; // struct UnwrapIfProperty< MemberProperty< ReadWrite > >

template < typename Owner, typename ValType,
  ValType Owner::*Member, std::size_t Index >
struct UnwrapIfProperty< ::prop::MemberProperty< Owner, ValType,
  Member, Index, ::prop::ReadOnly > >
  // read-only MemberProperty
{
  using Type = ValType;
  using Property = ::prop::MemberProperty< Owner, ValType,
    Member, Index, ::prop::ReadOnly >;

  static const Type& forward( const Property& value ) noexcept
  {
    return value.cref();
  }

}; // struct UnwrapIfProperty< MemberProperty< ReadOnly > >

template < typename Owner, typename ValType,
  typename ReadF, typename WriteFOrTag,
  std::size_t Index, typename TagOrVoid >
struct UnwrapIfProperty< ::prop::MethodProperty< Owner, ValType,
  ReadF, WriteFOrTag, Index, TagOrVoid > >
  // MethodProperty
{
  using Property = ::prop::MethodProperty<
    Owner, ValType, ReadF, WriteFOrTag, Index, TagOrVoid >;
  using Type = decltype( std::declval< Property >()() );

  static Type forward( const Property& value )
  {
    return value();
  }

}; // struct UnwrapIfProperty< MethodProperty >

template < typename Owner, typename PropType,
  PropType Owner::*Prop, std::size_t Index >
struct UnwrapIfProperty< ::prop::AliasProperty< Owner, PropType,
  Prop, Index, ::prop::ReadWrite > >
  // read-write AliasProperty - allow move from
  // if original property allows
{
  using Type = decltype( std::declval< PropType >()() );
  using Property = PropType;
  using AliasProperty = ::prop::AliasProperty< Owner, PropType,
    Prop, Index, ::prop::ReadWrite >;
  using UnwrapInner = UnwrapIfProperty< Property >;
  using OptimizedType = decltype( UnwrapInner::forward(
    std::move( std::declval< Property >()() ) ) );

  static Type forward( const AliasProperty& value )
  {
    return value.cref()();
  }

  static OptimizedType forward( AliasProperty&& value )
  {
    return UnwrapInner::forward( std::move( value.ref() ) );
  }
  
}; // struct UnwrapIfProperty< AliasProperty< ReadWrite > >

template < typename Owner, typename PropType,
  PropType Owner::*Prop, std::size_t Index >
struct UnwrapIfProperty< ::prop::AliasProperty< Owner, PropType,
  Prop, Index, ::prop::ReadOnly > >
  // read-only AliasProperty
{
  using Type = decltype( std::declval< PropType >()() );
  using Property = PropType;
  using AliasProperty = ::prop::AliasProperty< Owner, PropType,
    Prop, Index, ::prop::ReadOnly >;

  static Type forward( const AliasProperty& value )
  {
    return value.cref()();
  }

}; // struct UnwrapIfProperty< AliasProperty< ReadOnly > >

} // namespace detail
} // namespace prop
