#pragma once

namespace prop {
namespace detail {

/*
 * SetterArgumentMutator allows to pass to property
 * setter member function that receives rvalue reference
 * as parameter.
 * SetterArgumentMutator will take care of converting
 * passed value to rvalue if needed.
 */
template < typename SetterType, typename IncomingType,
           bool IsSetterArgumentRValueRef = false >
struct SetterArgumentMutator
// setter parameter is not rvalue reference, just forward value
{
  static const IncomingType& adapt( const IncomingType& value )
  {
    return value;
  }

  static IncomingType&& adapt( IncomingType&& value )
  {
    return std::move( value );
  }

}; // struct SetterArgumentMutator< SetterType, IncomingType, IsSetterArgumentRValueRef = false >

template < typename SameType >
struct SetterArgumentMutator< SameType, SameType, true >
// setter parameter is a rvalue reference
// and setter parameter type and value type are equal,
// create new object if value is const reference and
// forward if value is rvalue reference
{
  static SameType adapt( const SameType& value )
  {
    return value;
  }

  static SameType&& adapt( SameType&& value )
  {
    return std::move( value );
  }

}; // struct SetterArgumentMutator< SameType, SameType, IsSetterArgumentRValueRef = true >

template < typename SetterType, typename IncomingType >
struct SetterArgumentMutator< SetterType, IncomingType, true >
// setter parameter is a rvalue reference
// and setter parameter type and value type are not equal,
// always create new object
{
  static SetterType adapt( const IncomingType& value )
  {
    return static_cast< SetterType >( value );
  }

  static SetterType adapt( IncomingType&& value )
  {
    return static_cast< SetterType >( std::move( value ) );
  }

}; // struct SetterArgumentMutator< SetterType, IncomingType, IsSetterArgumentRValueRef = true >

} // namespace detail
} // namespace prop
