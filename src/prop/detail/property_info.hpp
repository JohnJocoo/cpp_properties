#pragma once

namespace prop {
namespace detail {

template < class OwnerType, class PropertyType,
  PropertyType OwnerType::*PropertyPtr >
class PropertyInfo
{
public:
  using Owner = OwnerType;
  using Property = PropertyType;
  using PropertyPointerType = Property Owner::*;
  using ValueType = typename Property::ValueType;
  using Accessor = typename Property::Accessor;
  
  static constexpr PropertyPointerType PropertyPointer = PropertyPtr;
  
}; // PropertyInfo

} // namespace detail
} // namespace prop
