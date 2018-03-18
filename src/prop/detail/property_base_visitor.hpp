#pragma once

#include "property_base.hpp"

namespace prop {
namespace detail {

template < typename Property >
struct PropertyBaseVisitor
{

  [[nodiscard]] static const Property& downcast(
    const PropertyBase< Property >& base ) noexcept
  {
    return base.downcast();
  }
  
  [[nodiscard]] static Property& downcast(
    PropertyBase< Property >& base ) noexcept
  {
    return base.downcast();
  }

}; // struct PropertyBaseVisitor

} // namespace detail
} // namespace prop
