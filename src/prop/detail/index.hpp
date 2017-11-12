#pragma once

#include <type_traits>
#include <cstddef>

namespace prop {
namespace detail {

template < std::size_t I >
class Index : public std::integral_constant< std::size_t, I >
{
}; // class Index

} // namespace detail
} // namespace prop
