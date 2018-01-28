#pragma once

#include <string>

struct StringHolder
{
  StringHolder() = default;
  StringHolder( const std::string& value )
  : string{ value }
  {
  }

  StringHolder& operator=( const std::string& other )
  {
    string = other;
    return *this;
  }
  
  std::string string;

};
