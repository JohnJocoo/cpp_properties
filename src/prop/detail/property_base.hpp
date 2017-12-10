#pragma once

namespace prop {
namespace detail {

template < typename ActualProperty >
class PropertyBase
{
protected:
  using Property = ActualProperty;
  
  [[nodiscard]] const Property& downcast() const noexcept
  {
    return *static_cast< const Property* >( this );
  }
  
  [[nodiscard]] Property& downcast() noexcept
  {
    return *static_cast< Property* >( this );
  }
  
}; // class PropertyBase

} // namespace detail
} // namespace prop
