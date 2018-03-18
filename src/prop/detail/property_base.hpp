#pragma once

namespace prop {
namespace detail {

template < typename Property >
struct PropertyBaseVisitor;

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
  
private:
  friend struct PropertyBaseVisitor< Property >;
  
}; // class PropertyBase

} // namespace detail
} // namespace prop
