#pragma once

#include "property_tags.hpp"
#include "forward_declarations.hpp"
#include "inner_traits.hpp"
#include "static_class_counter.hpp"
#include "property_method_base.hpp"
#include "member_function_wrappers.hpp"
#include "property_member_pointer_discoverer.hpp"
#include "unwrap_if_property.hpp"
#include "setter_argument_mutator.hpp"

#define PROP_DETAIL_METHOD_PROPERTY_GET_33fe95a2( value_type, name, getter, tag ) \
::prop::MethodProperty< zz_prop_owner_class_33fe95a2, value_type, \
::prop::detail::GetterWrapper< zz_prop_owner_class_33fe95a2, \
decltype( ::prop::detail::getReturnType( &zz_prop_owner_class_33fe95a2::getter ) )::Type, \
&zz_prop_owner_class_33fe95a2::getter >, tag, \
PROP_DETAIL_CURRENT_COUNTER_33fe95a2( zz_prop_owner_class_33fe95a2 ) > name; \
PROP_DETAIL_COUNTER_INC_33fe95a2( zz_prop_owner_class_33fe95a2 ) \
PROP_DETAIL_DECLARE_INFO_33fe95a2( zz_prop_owner_class_33fe95a2, name )

#define PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2( value_type, name, getter, setter, tag ) \
::prop::MethodProperty< zz_prop_owner_class_33fe95a2, value_type, \
::prop::detail::GetterWrapper< zz_prop_owner_class_33fe95a2, \
decltype( ::prop::detail::getReturnType( &zz_prop_owner_class_33fe95a2::getter ) )::Type, \
&zz_prop_owner_class_33fe95a2::getter >, \
::prop::detail::SetterWrapper< zz_prop_owner_class_33fe95a2, \
decltype( ::prop::detail::getArgumentType( &zz_prop_owner_class_33fe95a2::setter ) )::Type, \
&zz_prop_owner_class_33fe95a2::setter >, \
PROP_DETAIL_CURRENT_COUNTER_33fe95a2( zz_prop_owner_class_33fe95a2 ), tag > name; \
PROP_DETAIL_COUNTER_INC_33fe95a2( zz_prop_owner_class_33fe95a2 ) \
PROP_DETAIL_DECLARE_INFO_33fe95a2( zz_prop_owner_class_33fe95a2, name )

#define PROP_DETAIL_EXPAND_33fe95a2( x ) x

#define PROP_DETAIL_METHOD_PROPERTY_ERROR_33fe95a2(...) \
  static_assert(false, "Wrong number of arguments for PROP_METHOD_PROPERTY()")

#define PROP_DETAIL_GET_MACRO_33fe95a2(_1,_2,_3,_4,_5,NAME,...) NAME

#define PROP_METHOD_PROPERTY(...) PROP_DETAIL_EXPAND_33fe95a2( \
PROP_DETAIL_GET_MACRO_33fe95a2(__VA_ARGS__, \
PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2, PROP_DETAIL_METHOD_PROPERTY_GET_33fe95a2, \
PROP_DETAIL_METHOD_PROPERTY_ERROR_33fe95a2, PROP_DETAIL_METHOD_PROPERTY_ERROR_33fe95a2, \
PROP_DETAIL_METHOD_PROPERTY_ERROR_33fe95a2, PROP_DETAIL_METHOD_PROPERTY_ERROR_33fe95a2, \
PROP_DETAIL_METHOD_PROPERTY_ERROR_33fe95a2)(__VA_ARGS__))

namespace prop {

template < typename OwnerType, typename ValType,
  typename ReadF, std::size_t IndexInOwner >
// concept ImaginaryReadableProperty< T >
class MethodProperty< OwnerType, ValType, ReadF,
    ::prop::ReadOnly, IndexInOwner, void > :
  public ::prop::detail::PropertyMethodBase<
    MethodProperty< OwnerType, ValType, ReadF,
      ::prop::ReadOnly, IndexInOwner, void >,
    OwnerType, ValType, ReadF >
{
public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadOnly;

private:
  static_assert( ::prop::detail::IsPropertyValueGood< ValueType >::value,
    PROP_DETAIL_IS_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 );
  static_assert( std::is_same< ValueType, typename ReadF::CleanReturnType >::value,
    "Member property type must be the same as getter return type.");

  static constexpr std::size_t Index = IndexInOwner;

private:
  MethodProperty()
  {
    static_assert( ::prop::detail::IsOwnerGood< Owner >::value,
      PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 );
  }

  MethodProperty( const MethodProperty& ) = default;
  MethodProperty( MethodProperty&& ) = default;
  ~MethodProperty() = default;
  
public:
  template < typename V >
  MethodProperty& operator=( V&& ) = delete;
  MethodProperty& operator=( const MethodProperty& ) = delete;
  MethodProperty& operator=( MethodProperty&& ) = delete;
  
private:
  friend OwnerType;
  friend ::prop::detail::UnwrapIfProperty< MethodProperty >;

}; // class MethodProperty< ReadOnly >

template < typename OwnerType, typename ValType,
  typename ReadF, typename WriteF, std::size_t IndexInOwner >
// concept ImaginaryReadableProperty< T >
// concept WritableProperty< T >
class MethodProperty< OwnerType, ValType,
    ReadF, WriteF, IndexInOwner, ::prop::ReadWrite > :
  public ::prop::detail::PropertyMethodBase<
    MethodProperty< OwnerType, ValType,
      ReadF, WriteF, IndexInOwner, ::prop::ReadWrite>,
    OwnerType, ValType, ReadF >
{
public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadWrite;

private:
  static_assert( ::prop::detail::IsPropertyValueGood< ValueType >::value,
    PROP_DETAIL_IS_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 );
  static_assert( std::is_same< ValueType, typename ReadF::CleanReturnType >::value,
    "Member property type must be the same as getter return type.");
  static_assert( std::is_same< ValueType, typename WriteF::CleanArgumentType >::value,
    "Member property type must be the same as setter argument type.");
  static_assert((std::is_lvalue_reference< typename WriteF::ArgumentType >::value
                  && std::is_const< typename std::remove_reference<
                       typename WriteF::ArgumentType >::type >::value)
                || std::is_same< typename WriteF::ArgumentType,
                     typename WriteF::CleanArgumentType >::value
                || std::is_rvalue_reference< typename WriteF::ArgumentType >::value,
    "Invalid setter argument type: only T, const T& and T&& are allowed");

  static constexpr std::size_t Index = IndexInOwner;

private:
  MethodProperty()
  {
    static_assert( ::prop::detail::IsOwnerGood< Owner >::value,
      PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 );
  }

  MethodProperty( const MethodProperty& ) = default;
  MethodProperty( MethodProperty&& ) = default;
  ~MethodProperty() = default;

public:
  template < typename V >
  MethodProperty& operator=( V&& uref )
  {
    set( std::forward< V >( uref ) );
    return *this;
  }

  MethodProperty& operator=( const MethodProperty& other )
  {
    set( other() );
    return *this;
  }

private:
  template < typename V >
  void set( V&& uref )
  {
    using Unwrapper = ::prop::detail::UnwrapIfProperty<
      typename ::prop::detail::CleanType< V > >;
    using IncomingType = typename Unwrapper::Type;
    using Mutator = ::prop::detail::SetterArgumentMutator<
      typename WriteF::CleanArgumentType, IncomingType,
      std::is_rvalue_reference< typename WriteF::ArgumentType >::value >;
    
    (this->owner_ref().*(WriteF::Pointer))( Mutator::adapt(
      Unwrapper::forward( std::forward< V >( uref ) ) ) );
  }
  
private:
  friend OwnerType;
  friend ::prop::detail::UnwrapIfProperty< MethodProperty >;

}; // class MethodProperty< ReadWrite >

} // namespace prop
