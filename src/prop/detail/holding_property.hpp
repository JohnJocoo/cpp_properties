#pragma once

#include "property_tags.hpp"
#include "forward_declarations.hpp"
#include "property_real_value_base.hpp"
#include "property_holding_base.hpp"
#include "inner_traits.hpp"
#include "static_class_counter.hpp"
#include "unwrap_if_property.hpp"
#include "property_operators_common.hpp"

#define PROP_HOLDING_PROPERTY( value_type, name, accessor_tag ) \
::prop::HoldingProperty< zz_prop_owner_class_33fe95a2, value_type, \
PROP_DETAIL_CURRENT_COUNTER_33fe95a2( zz_prop_owner_class_33fe95a2 ), accessor_tag > name; \
PROP_DETAIL_COUNTER_INC_33fe95a2( zz_prop_owner_class_33fe95a2 )

namespace prop {

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner >
// concept OwningReadableProperty< T >
class HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadOnly > :
  public ::prop::detail::PropertyRealValueBase<
    HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadOnly >, ValType >,
  private ::prop::detail::PropertyHoldingBase< ValType >
{
public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadOnly;

private:
  static_assert( ::prop::detail::IsPropertyValueGood< ValueType >::value,
    PROP_DETAIL_IS_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 );

  static constexpr std::size_t Index = IndexInOwner;
  using Base = ::prop::detail::PropertyHoldingBase< ValueType >;

private: // Can be accessed by owner class
  template < typename... V >
  HoldingProperty( V&&... uref )
    : Base{ std::forward< V >( uref )... }
  {
    static_assert( ::prop::detail::IsOwnerGood< Owner >::value,
      PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 );
  }
  
  HoldingProperty( const HoldingProperty& ) = default;
  HoldingProperty( HoldingProperty&& ) = default;
  ~HoldingProperty() = default;
  
  HoldingProperty& operator=( const HoldingProperty& ) = default;
  HoldingProperty& operator=( HoldingProperty&& ) = default;
  
  template < typename V >
  HoldingProperty& operator=( V&& uref )
  {
    Base::copy( std::forward< V >( uref ) );
    return *this;
  }

  friend OwnerType;
  friend ::prop::detail::UnwrapIfProperty< HoldingProperty >;
  friend ::prop::detail::PropertyRealValueVisitor< HoldingProperty >;

}; // class HoldingProperty< ReadOnly >

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner >
// concept OwningReadableProperty< T >
// concept WritableProperty< T >
class HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadWrite > :
  public ::prop::detail::PropertyRealValueBase<
    HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadWrite >, ValType >,
  private ::prop::detail::PropertyHoldingBase< ValType >
{
public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadWrite;

private:
  static_assert( ::prop::detail::IsPropertyValueGood< ValueType >::value,
    PROP_DETAIL_IS_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 );

  static constexpr std::size_t Index = IndexInOwner;
  using Base = ::prop::detail::PropertyHoldingBase< ValueType >;

private: // Can be accessed by owner class
  template < typename... V >
  HoldingProperty( V&&... uref )
    : Base{ std::forward< V >( uref )... }
  {
    static_assert( ::prop::detail::IsOwnerGood< Owner >::value,
      PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 );
  }
  
  HoldingProperty( const HoldingProperty& ) = default;
  HoldingProperty( HoldingProperty&& ) = default;
  ~HoldingProperty() = default;

public:
  HoldingProperty& operator=( const HoldingProperty& ) = default;
  HoldingProperty& operator=( HoldingProperty&& ) = default;
  
  template < typename V >
  HoldingProperty& operator=( V&& uref )
  {
    Base::copy( std::forward< V >( uref ) );
    return *this;
  }
  
private:
  friend OwnerType;
  friend ::prop::detail::UnwrapIfProperty< HoldingProperty >;
  friend ::prop::detail::PropertyRealValueVisitor< HoldingProperty >;

}; // class HoldingProperty< ReadWrite >

} // namespace prop
