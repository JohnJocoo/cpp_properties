#pragma once

namespace prop {
namespace detail {

template < typename T, typename GrainAccess >
class ValueHolder
{
  template < typename... V >
  ValueHolder( V&&... uref )
    : m_value{ std::forward< V >( uref )... }
  {
  }

 T m_value;
 
 friend GrainAccess;

}; // struct Identity

} // namespace detail
} // namespace prop

