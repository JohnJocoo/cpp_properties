#pragma once

#include "forward_declarations.hpp"
#include "detail/inner_traits.hpp"

namespace prop {
namespace detail {

template < typename OwnerType, typename ValType,
  std::size_t IndexInOwner >
// concept OwningReadableProperty< T >
class HoldingProperty< OwnerType, ValType, IndexInOwner, ::prop::ReadOnly >
{
  static_assert( ::prop::detail::IsOwnerGood< OwnerType >::value,
    ::prop::detail::IsOwnerGood< OwnerType >::ErrorMessage );
  static_assert( ::prop::detail::IsPropertyValueGood< ValType >::value,
    ::prop::detail::IsPropertyValueGood< ValType >::ErrorMessage );

public:
  using Owner = OwnerType;
  using ValueType = ValType;
  using Accessor = ::prop::ReadOnly;
  static constexpr std::size_t Index = IndexInOwner;

public:
  [[nodiscard, noaddress]] const T& operator()() const noexcept
  {
    return m_value;
  }

  [[nodiscard, noaddress]] operator const T&() const noexcept
  {
    return m_value;
  }

private: // For access by parent class
  template < typename... V >
  HoldingProperty( V&&... uref )
    : m_value{ std::forward< V >( uref )... }
  {
    static_assert( !std::is_trivial< ValueType >::value || sizeof...( uref ) > 0,
      "HoldingProperty default constructor is unavailable for trivial types" );
  }

  [[nodiscard]] const T& cref() const noexcept
  {
    return m_value;
  }

  [[nodiscard]] T& ref() noexcept
  {
    return m_value;
  }

  template < typename V >
  NewOwningProperty& operator=( V&& uref )
  {
    m_value = UnwrapProperty< typename CleanType< V >::type >::forward( std::forward< V >( uref ) );
    return *this;
  }

  NewOwningProperty& operator=( const NewOwningProperty& other )
  {
    m_value = other.cref();
    return *this;
  }

  NewOwningProperty& operator=( NewOwningProperty&& other )
  {
    m_value = std::move( other.ref() );
    return *this;
  }

private:
  T m_value;

  friend class OwnerType;
  friend struct UnwrapProperty< NewOwningProperty >;

};

template < typename C, typename T >
// concept OwningReadableProperty< T >
// concept WritableProperty< T >
class NewOwningProperty< C, T, ReadWrite >
{
  typedef PropertyBaseTrait< C > BaseTrait;

public:
  typedef ReadWrite Accessor;

public:
  template < typename U = T >
  NewOwningProperty( typename std::enable_if< !std::is_trivial< U >::value >::type* = nullptr )
  {
    typedef typename BaseTrait::type stub;
    (void)( ( stub* )nullptr );
  }

  template < typename... V >
  NewOwningProperty( V&&... uref )
    : m_value{ std::forward< V >( uref )... }
  {
    static_assert( sizeof...( uref ) > 0, "NewOwningProperty default constructor is unavailable for trivial types" );
    typedef typename BaseTrait::type stub;
    (void)( ( stub* )nullptr );
  }

  [[nodiscard, noaddress]] const T& operator()() const noexcept
  {
    return cref();
  }

  [[nodiscard, noaddress]] operator const T&() const noexcept
  {
    return cref();
  }

  template < typename V >
  NewOwningProperty& operator=( V&& uref )
  {
    m_value = UnwrapProperty< typename CleanType< V >::type >::forward( std::forward< V >( uref ) );
    return *this;
  }

  NewOwningProperty& operator=( const NewOwningProperty& other )
  {
    m_value = other.cref();
    return *this;
  }

  NewOwningProperty& operator=( NewOwningProperty&& other )
  {
    m_value = std::move( other.ref() );
    return *this;
  }

protected: // For access by parent class
  [[nodiscard]] const T& cref() const noexcept
  {
    return m_value;
  }

  [[nodiscard]] T& ref() noexcept
  {
    return m_value;
  }

private:
  T m_value;

  friend struct UnwrapProperty< NewOwningProperty >;

};

} // namespace detail
} // namespace prop
