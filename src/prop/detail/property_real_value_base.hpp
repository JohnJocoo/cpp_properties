#pragma once

#include "property_base.hpp"
#include "property_real_value_visitor.hpp"

namespace prop {
namespace detail {

template < typename ActualProperty, typename ValueType >
class PropertyRealValueBase : public ::prop::detail::PropertyBase< ActualProperty >
{
public:
  [[nodiscard, prop::noaddress]] const ValueType& operator()() const & noexcept
  {
    return ::prop::detail::PropertyRealValueVisitor< ActualProperty >::read(
      this->downcast() );
  }

  /*
   * const volatile & is used to fix "ambiguos" call
   * on clang and visual studio
   */
  [[nodiscard, prop::noaddress]] operator const ValueType& () const volatile & noexcept
  {
    return ::prop::detail::PropertyRealValueVisitor< ActualProperty >::read(
      const_cast< const PropertyRealValueBase* >( this )->downcast() );
  }
  
  /*
   * I've decided to give ability to move from ReadOnly
   * properties, as moving-from usually occures on
   * objects that won't be used any more.
   * TODO: move to docs 17.6.5.15 [lib.types.movedfrom]
   * Objects of types defined in the C++ standard library may be moved from (12.8).
   * Move operations may be explicitly specified or implicitly generated.
   * Unless otherwise specified, such moved-from objects shall be placed in a valid but unspecified state.
   *
   * ReadOnly property is not equal to const objects
   * (as it might be changed by owner). So I've decided
   * to allow move-from ReadOnly properties, with
   * obvious contract that property shouldn't be used
   * any more (owner will be destroyed).
   */
  [[nodiscard, prop::noaddress]] operator ValueType&& () && noexcept
  {
    return ::prop::detail::PropertyRealValueVisitor< ActualProperty >::move(
      this->downcast() );
  }
  
}; // class PropertyRealValueBase

} // namespace detail
} // namespace prop
