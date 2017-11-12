#pragma once

namespace prop {

template < typename CuriousProperty >
class PropertyBase
{
public:
  using Property = CuriousProperty;
  
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
