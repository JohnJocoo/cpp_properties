#pragma once

#include "property_base.hpp"
#include "property_base_visitor.hpp"
#include "property_real_value_base.hpp"
#include "property_real_value_visitor.hpp"
#include "inner_traits.hpp"
#include "unwrap_if_property.hpp"

#define PROP_DETAIL_DEFINE_UNARY_PREFIX_REAL_VALUE_33fe95a2( op ) \
template < typename ActualProperty, typename ValueType, \
  typename std::enable_if< std::is_same< typename ActualProperty::Accessor, \
    typename ::prop::ReadWrite >::value, int >::type = 0  > \
ActualProperty& operator op( PropertyRealValueBase< ActualProperty, ValueType >& property ) \
{ \
  ActualProperty& actual = PropertyBaseVisitor< ActualProperty >::downcast( property ); \
  auto& value = PropertyRealValueVisitor< ActualProperty >::read( actual ); \
  op value; \
  return actual; \
}

#define PROP_DETAIL_DEFINE_UNARY_POSTFIX_REAL_VALUE_33fe95a2( op ) \
template < typename ActualProperty, typename ValueType, \
  typename std::enable_if< std::is_same< typename ActualProperty::Accessor, \
    typename ::prop::ReadWrite >::value, int >::type = 0 > \
ValueType operator op( PropertyRealValueBase< ActualProperty, ValueType >& property, int ) \
{ \
  ActualProperty& actual = PropertyBaseVisitor< ActualProperty >::downcast( property ); \
  auto& value = PropertyRealValueVisitor< ActualProperty >::read( actual ); \
  return value op; \
}

#define PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( op ) \
template < typename ActualProperty, typename ValueType, typename V, \
  typename std::enable_if< std::is_same< typename ActualProperty::Accessor, \
    typename ::prop::ReadWrite >::value, int >::type = 0 > \
ActualProperty& operator op( PropertyRealValueBase< ActualProperty, ValueType >& property, V&& uref ) \
{ \
  ActualProperty& actual = PropertyBaseVisitor< ActualProperty >::downcast( property ); \
  auto& value = PropertyRealValueVisitor< ActualProperty >::read( actual ); \
  value op ::prop::detail::UnwrapIfProperty< \
      typename ::prop::detail::CleanType< V > >::forward( \
        std::forward< V >( uref ) ); \
  return actual; \
}

namespace prop {
namespace detail {

PROP_DETAIL_DEFINE_UNARY_PREFIX_REAL_VALUE_33fe95a2( ++ )
PROP_DETAIL_DEFINE_UNARY_PREFIX_REAL_VALUE_33fe95a2( -- )
PROP_DETAIL_DEFINE_UNARY_POSTFIX_REAL_VALUE_33fe95a2( ++ )
PROP_DETAIL_DEFINE_UNARY_POSTFIX_REAL_VALUE_33fe95a2( -- )

PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( += )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( -= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( *= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( /= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( %= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( &= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( |= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( ^= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( <<= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_REAL_VALUE_33fe95a2( >>= )

} // namespace detail
} // namespace prop
