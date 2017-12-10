#pragma once

#include "property_tags.hpp"
#include "detail/forward_declarations.hpp"
#include "detail/inner_traits.hpp"
#include "detail/value_holder.hpp"
#include "detail/unwrap_if_property.hpp"
#include "detail/static_class_counter.hpp"
#include "detail/holding_property_facade.hpp"
#include "detail/property_real_value_base.hpp"

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
    HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadOnly >, ValType >
{
public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadOnly;

private:
  static_assert( ::prop::detail::IsRWPropertyValueGood< ValueType >::value,
    PROP_DETAIL_IS_RW_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 );

  using Holder = typename ::prop::detail::ValueHolder< ValueType, HoldingProperty >;
  static constexpr std::size_t Index = IndexInOwner;

private: // Can be accessed by owner class
  template < typename... V >
  HoldingProperty( V&&... uref )
    : m_holder{ std::forward< V >( uref )... }
  {
    static_assert( ::prop::detail::IsOwnerGood< Owner >::value,
      PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 );
  
    static_assert( !std::is_trivial< ValueType >::value || sizeof...( uref ) > 0,
      "HoldingProperty default constructor is unavailable for trivial types" );
  }

  [[nodiscard]] const ValueType& cref() const noexcept
  {
    return m_holder.m_value;
  }

  [[nodiscard]] ValueType& ref() noexcept
  {
    return m_holder.m_value;
  }

  template < typename V >
  HoldingProperty& operator=( V&& uref )
  {
    m_holder.m_value = ::prop::detail::UnwrapIfProperty<
      typename ::prop::detail::CleanType< V > >::forward(
        std::forward< V >( uref ) );
    return *this;
  }

  HoldingProperty& operator=( const HoldingProperty& other )
  {
    m_holder.m_value = other.cref();
    return *this;
  }

  HoldingProperty& operator=( HoldingProperty&& other )
  {
    m_holder.m_value = std::move( other.ref() );
    return *this;
  }

private:
  Holder m_holder;

  friend OwnerType;
  friend ::prop::detail::UnwrapIfProperty< HoldingProperty >;
  friend ::prop::detail::PropertyRealValueFacade< HoldingProperty >;

}; // class HoldingProperty< ReadOnly >

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner >
// concept OwningReadableProperty< T >
// concept WritableProperty< T >
class HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadWrite > :
  public ::prop::detail::PropertyRealValueBase<
    HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadWrite >, ValType >
{
public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadWrite;

public:  
  template < typename V >
  HoldingProperty& operator=( V&& uref )
  {
    m_holder.m_value = ::prop::detail::UnwrapIfProperty<
      typename ::prop::detail::CleanType< V > >::forward(
        std::forward< V >( uref ) );
    return *this;
  }

  HoldingProperty& operator=( const HoldingProperty& other )
  {
    m_holder.m_value = other.cref();
    return *this;
  }

  HoldingProperty& operator=( HoldingProperty&& other )
  {
    m_holder.m_value = std::move( other.ref() );
    return *this;
  }

private:
  static_assert( ::prop::detail::IsRWPropertyValueGood< ValueType >::value,
    PROP_DETAIL_IS_RW_PROPERTY_VALUE_GOOD_ERROR_33fe95a2 );

  using Holder = typename ::prop::detail::ValueHolder< ValueType, HoldingProperty >;
  static constexpr std::size_t Index = IndexInOwner;

private: // Can be accessed by owner class
  template < typename... V >
  HoldingProperty( V&&... uref )
    : m_holder{ std::forward< V >( uref )... }
  {
    static_assert( ::prop::detail::IsOwnerGood< Owner >::value,
      PROP_DETAIL_IS_OWNER_GOOD_ERROR_33fe95a2 );
  
    static_assert( !std::is_trivial< ValueType >::value || sizeof...( uref ) > 0,
      "HoldingProperty default constructor is unavailable for trivial types" );
  }

  [[nodiscard]] const ValueType& cref() const noexcept
  {
    return m_holder.m_value;
  }

  [[nodiscard]] ValueType& ref() noexcept
  {
    return m_holder.m_value;
  }

private:
  Holder m_holder;

  friend OwnerType;
  friend ::prop::detail::UnwrapIfProperty< HoldingProperty >;
  friend ::prop::detail::PropertyRealValueFacade< HoldingProperty >;

}; // class HoldingProperty< ReadWrite >

} // namespace prop
