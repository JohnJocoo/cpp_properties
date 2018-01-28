#pragma once

#include <cstddef>

#include "index.hpp"

#define PROP_DETAIL_CURRENT_COUNTER_33fe95a2( class ) \
::prop::detail::CurrentCounter< class, __COUNTER__ >::value

#define PROP_DETAIL_COUNTER_INC_33fe95a2( class ) \
static constexpr void zz_prop_detail_counter_33fe95a2( \
::prop::detail::Index< PROP_DETAIL_CURRENT_COUNTER_33fe95a2( class ) > ) {}

namespace prop {
namespace detail {

template < typename Class, std::size_t N, int UID >
class HasStaticCounter
{
  template< typename T, T >
  struct helper;
  template< typename T >
  static std::uint8_t check( helper< void (*)( ::prop::detail::Index< N > ),
                            &T::zz_prop_detail_counter_33fe95a2 >* );
  template< typename T >
  static std::uint16_t check(...);
  
public:
  static constexpr bool value = sizeof( check< Class >( 0 ) ) == sizeof( std::uint8_t );
  
}; // class HasStaticCounter

template < typename Class, std::size_t N, int UID >
struct FirstAbsentCounter
{
  static constexpr std::size_t value = std::conditional_t<
    ::prop::detail::HasStaticCounter< Class, N, UID >::value,
      ::prop::detail::FirstAbsentCounter< Class, N + 1, UID >,
      ::prop::detail::Index< N > >::value;

}; // struct FirstAbsentCounter

template < typename Class, int UID >
struct CurrentCounter
{
  static constexpr std::size_t value =
    ::prop::detail::FirstAbsentCounter< Class, 0, UID >::value;

}; // struct CurrentCounter

} // namespace detail
} // namespace prop
