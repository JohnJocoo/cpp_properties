#pragma once

#include "forward_declarations.hpp"

namespace prop {
namespace detail {

template < typename Property >
struct PropertyRealValueVisitor
{
}; // struct PropertyRealValueVisitor

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner, typename AccessorTag >
struct PropertyRealValueVisitor< ::prop::HoldingProperty<
  OwnerType, ValType, IndexInOwner, AccessorTag> >
{
  using ValueType = ValType;
  using Property = ::prop::HoldingProperty<
    OwnerType, ValType, IndexInOwner, AccessorTag >;

  [[nodiscard]] static const ValueType& read( const Property& property ) noexcept
  {
    return property.cref();
  }
  
  [[nodiscard]] static ValueType& read( Property& property ) noexcept
  {
    return property.ref();
  }
  
  [[nodiscard]] static ValueType&& move( Property& property ) noexcept
  {
    return std::move( property.ref() );
  }

}; // class PropertyRealValueVisitor< HoldingProperty >

} // namespace detail
} // namespace prop
