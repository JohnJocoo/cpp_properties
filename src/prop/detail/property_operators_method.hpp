#pragma once

#include "method_property.hpp"
#include "inner_traits.hpp"
#include "unwrap_if_property.hpp"

#include <iosfwd>

#define PROP_DETAIL_DEFINE_UNARY_PREFIX_METHOD_33fe95a2( op ) \
template < typename OwnerType, typename ValType, \
  typename ReadF, typename WriteF, std::size_t IndexInOwner > \
MethodProperty< OwnerType, ValType, \
  ReadF, WriteF, IndexInOwner, ::prop::ReadWrite >& \
operator op( MethodProperty< OwnerType, ValType, \
    ReadF, WriteF, IndexInOwner, ::prop::ReadWrite >& property ) \
{ \
  auto value = property(); \
  op value; \
  property = std::move( value ); \
  return property; \
}

#define PROP_DETAIL_DEFINE_UNARY_POSTFIX_METHOD_33fe95a2( op ) \
template < typename OwnerType, typename ValType, \
  typename ReadF, typename WriteF, std::size_t IndexInOwner > \
auto operator op( MethodProperty< OwnerType, ValType, \
    ReadF, WriteF, IndexInOwner, ::prop::ReadWrite >& property, int ) \
{ \
  auto value = property(); \
  auto saved = value op; \
  property = std::move( value ); \
  return saved; \
}

#define PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( op ) \
template < typename OwnerType, typename ValType, \
  typename ReadF, typename WriteF, std::size_t IndexInOwner, \
  typename V > \
MethodProperty< OwnerType, ValType, \
  ReadF, WriteF, IndexInOwner, ::prop::ReadWrite >& \
operator op( MethodProperty< OwnerType, ValType, \
    ReadF, WriteF, IndexInOwner, ::prop::ReadWrite >& property, V&& uref ) \
{ \
  auto value = property(); \
  value op ::prop::detail::UnwrapIfProperty< \
      typename ::prop::detail::CleanType< V > >::forward( \
        std::forward< V >( uref ) ); \
  property = std::move( value ); \
  return property; \
}

namespace prop {
namespace detail {

PROP_DETAIL_DEFINE_UNARY_PREFIX_METHOD_33fe95a2( ++ )
PROP_DETAIL_DEFINE_UNARY_PREFIX_METHOD_33fe95a2( -- )
PROP_DETAIL_DEFINE_UNARY_POSTFIX_METHOD_33fe95a2( ++ )
PROP_DETAIL_DEFINE_UNARY_POSTFIX_METHOD_33fe95a2( -- )

PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( += )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( -= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( *= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( /= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( %= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( &= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( |= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( ^= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( <<= )
PROP_DETAIL_DEFINE_BINARY_MUTABLE_METHOD_33fe95a2( >>= )

// overload >> stream input operator

template < typename OwnerType, typename ValType,
  typename ReadF, typename WriteF, std::size_t IndexInOwner >
::std::istream& operator >>( ::std::istream& is,
  MethodProperty< OwnerType, ValType,
    ReadF, WriteF, IndexInOwner, ::prop::ReadWrite >& property )
{
  auto value = property();
  is >> value;
  property = std::move( value );
  return is;
}

} // namespace detail
} // namespace prop
