#pragma once

#include "property_base.hpp"
#include "property_base_visitor.hpp"
#include "inner_traits.hpp"
#include "unwrap_if_property.hpp"

#define PROP_DETAIL_DEFINE_UNARY_IMMUTABLE_33fe95a2( op ) \
template < typename Property > \
auto operator op( const PropertyBase< Property >& property ) \
{ \
  return op PropertyBaseVisitor< Property >::downcast( property )(); \
}

#define PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( op ) \
template < typename Property, typename T > \
auto operator op( const PropertyBase< Property >& property, const T& value ) \
{ \
  return PropertyBaseVisitor< Property >::downcast( property )() op \
    UnwrapIfProperty< T >::forward( value ); \
} \
 \
template < typename T, typename Property, \
  typename std::enable_if< !IsProperty< CleanType< T > >::value, \
    int >::type = 0 > \
auto operator op( const T& value, const PropertyBase< Property >& property ) \
{ \
  return value op PropertyBaseVisitor< Property >::downcast( property )(); \
}

namespace prop {
namespace detail {

PROP_DETAIL_DEFINE_UNARY_IMMUTABLE_33fe95a2( + )
PROP_DETAIL_DEFINE_UNARY_IMMUTABLE_33fe95a2( - )
PROP_DETAIL_DEFINE_UNARY_IMMUTABLE_33fe95a2( ~ )
PROP_DETAIL_DEFINE_UNARY_IMMUTABLE_33fe95a2( ! )

PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( + )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( - )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( * )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( / )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( % )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( & )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( | )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( ^ )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( == )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( != )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( < )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( > )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( <= )
PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( >= )
//TODO: PROP_DETAIL_DEFINE_BINARY_IMMUTABLE_33fe95a2( <=> )

// overload << shift and stream output operator

template < typename Property, typename T >
auto operator <<( const PropertyBase< Property >& property, const T& value )
{
  return PropertyBaseVisitor< Property >::downcast( property )() <<
    UnwrapIfProperty< T >::forward( value );
}
 
template < typename T, typename Property,
  typename std::enable_if< !IsProperty< CleanType< T > >::value
      && !::std::is_base_of< ::std::ostream, CleanType< T > >::value,
    int >::type = 0 >
auto operator <<( const T& value, const PropertyBase< Property >& property )
{
  return value << PropertyBaseVisitor< Property >::downcast( property )();
}

template < typename Property >
::std::ostream& operator <<( ::std::ostream& os, const PropertyBase< Property >& property )
{
  return os << PropertyBaseVisitor< Property >::downcast( property )();
}

// overload >> shift,
// >> stream input operator will be overloaded in
// property-specific file

template < typename Property, typename T >
auto operator >>( const PropertyBase< Property >& property, const T& value )
{
  return PropertyBaseVisitor< Property >::downcast( property )() >>
    UnwrapIfProperty< T >::forward( value );
}
 
template < typename T, typename Property,
  typename std::enable_if< !IsProperty< CleanType< T > >::value
      && !::std::is_base_of< ::std::istream, CleanType< T > >::value,
    int >::type = 0 >
auto operator >>( const T& value, const PropertyBase< Property >& property )
{
  return value >> PropertyBaseVisitor< Property >::downcast( property )();
}

} // namespace detail
} // namespace prop
