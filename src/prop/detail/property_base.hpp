#pragma once

namespace prop {

template < typename ActualProperty >
class PropertyBase
{
public:
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

} // namespace prop
