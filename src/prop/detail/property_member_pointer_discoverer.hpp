#pragma once

#include "index.hpp"
#include "property_info.hpp"
#include "property_index.hpp"

#define PROP_DETAIL_DECLARE_INFO_33fe95a2( class, property_name ) \
static constexpr ::prop::detail::PropertyInfo< class, \
decltype( class::property_name ), &class::property_name > \
zz_prop_detail_info_33fe95a2( ::prop::detail::Index< \
::prop::detail::PropertyIndex< decltype( class::property_name ) >::value > ) \
{ return {}; }

namespace prop {
namespace detail {

template < typename Owner, typename Property >
constexpr auto discoverProperty()
{
  return decltype( Owner::zz_prop_detail_info_33fe95a2(
    ::prop::detail::Index< ::prop::detail::PropertyIndex< Property >::value >{} ) ){};
}

template < typename Owner, typename Property >
constexpr Property Owner::* discoverPropertyPointer()
{
  return decltype( discoverProperty< Owner, Property >() )::PropertyPointer;
}

} // namespace detail
} // namespace prop
