#pragma once

#include "property_real_value_facade.hpp"
#include "forward_declarations.hpp"

namespace prop {
namespace detail {

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner, typename AccessorTag >
struct PropertyRealValueFacade< ::prop::HoldingProperty<
  OwnerType, ValType, IndexInOwner, AccessorTag> >
{
  using ValueType = ValType;
  using Property = ::prop::HoldingProperty<
    OwnerType, ValType, IndexInOwner, AccessorTag >;

  [[nodiscard]] static const ValueType& read( const Property& property ) noexcept
  {
    return property.cref();
  }
  
  [[nodiscard]] static ValueType&& move( Property& property ) noexcept
  {
    return std::move( property.ref() );
  }

}; // class PropertyRealValueFacade< HoldingProperty >

} // namespace detail
} // namespace prop
