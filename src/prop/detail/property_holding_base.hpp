#pragma once

#include <type_traits>

#include "forward_declarations.hpp"
#include "unwrap_if_property.hpp"
#include "inner_traits.hpp"

#define PROP_DETAIL_HOLDING_PROPERTY_TRIVIAL_ERROR_33fe95a2 \
"HoldingProperty default constructor is unavailable for trivial types"

namespace prop {
namespace detail {

template < typename T >
class PropertyHoldingBase
{
  using ValueType = T;

protected:
  template < typename... V >
  PropertyHoldingBase( V&&... uref )
    : m_value{ std::forward< V >( uref )... }
  {
    static_assert( !std::is_trivial< ValueType >::value || sizeof...( uref ) > 0,
      PROP_DETAIL_HOLDING_PROPERTY_TRIVIAL_ERROR_33fe95a2 );
  }
  
  PropertyHoldingBase( const PropertyHoldingBase& ) = default;
  PropertyHoldingBase( PropertyHoldingBase&& ) = default;
  
  [[nodiscard]] const ValueType& cref() const noexcept
  {
    return m_value;
  }

  [[nodiscard]] ValueType& ref() noexcept
  {
    return m_value;
  }
  
  template < typename V >
  void copy( V&& uref )
  {
    m_value = ::prop::detail::UnwrapIfProperty<
      typename ::prop::detail::CleanType< V > >::forward(
        std::forward< V >( uref ) );
  }

  PropertyHoldingBase& operator=( const PropertyHoldingBase& other )
  {
    m_value = other.cref();
    return *this;
  }

  PropertyHoldingBase& operator=( PropertyHoldingBase&& other )
  {
    m_value = std::move( other.ref() );
    return *this;
  }
  
private:
  ValueType m_value;
  
}; // class PropertyHoldingBase

} // namespace detail
} // namespace prop
