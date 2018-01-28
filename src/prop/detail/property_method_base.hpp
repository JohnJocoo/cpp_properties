#pragma once

#include "property_base.hpp"
#include "owner_pointer_reparator.hpp"

#include <type_traits>

namespace prop {
namespace detail {

// TODO: make return type conditionally reference
// if getter returns reference
template < typename ActualProperty, typename Owner,
  typename ReturnedType, typename GetterWrapper >
class PropertyMethodBase : public ::prop::detail::PropertyBase< ActualProperty >
{
  static_assert(!std::is_reference< ReturnedType >::value,
    "Member property must return by value.");

public:
  [[nodiscard]] ReturnedType operator()() const &
  {
    return (owner_cref().*(GetterWrapper::Pointer))();
  }

  [[nodiscard]] operator ReturnedType () const &
  {
    return (owner_cref().*(GetterWrapper::Pointer))();
  }
  
protected:
  Owner& owner_ref()
  {
    return *::prop::detail::repairOwnerPointer<
      Owner, ActualProperty >( &this->downcast() );
  }
  
  const Owner& owner_cref() const
  {
    return *::prop::detail::repairOwnerPointer<
      const Owner, const ActualProperty >( &this->downcast() );
  }
  
}; // class PropertyMethodBase

} // namespace detail
} // namespace prop
