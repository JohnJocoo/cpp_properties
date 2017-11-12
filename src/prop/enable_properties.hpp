#pragma once

#define PROP_ENABLE_PROPERTIES( class ) using zz_prop_owner_class = class;

namespace prop {
  
struct EnableProperties
{
  EnableProperties() = default;
  EnableProperties( const EnableProperties& ) = default;
  EnableProperties( EnableProperties&& ) = default;
  ~EnableProperties() = default;

  // delete default assignment operator for child classes
  // because of "multiple copy" problem
  EnableProperties& operator=( const EnableProperties& ) = delete;
  EnableProperties& operator=( EnableProperties&& ) = delete;

}; // struct EnableProperties

} // namespace prop
