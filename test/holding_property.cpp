#include <gtest/gtest.h>

#include <prop/holding_property.hpp>

#include <string>

class BasicHoldingProperties : prop::EnableProperties
{
public:
  BasicHoldingProperties()
  : int_value{ 0 }
  , ro_int_value{ 0 }
  {}

public:
  PROP_ENABLE_PROPERTIES( BasicHoldingProperties )
  PROP_HOLDING_PROPERTY( int, int_value, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( std::string, string_value, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( int, ro_int_value, prop::ReadOnly )
  PROP_HOLDING_PROPERTY( std::string, ro_string_value, prop::ReadOnly )
};

TEST(HoldingProperty, Types)
{
  BasicHoldingProperties obj;
}

TEST(HoldingProperty, Traits)
{

}

TEST(HoldingProperty, Get)
{

}

TEST(HoldingProperty, Set)
{

}

TEST(HoldingProperty, MoveTo)
{

}

TEST(HoldingProperty, MoveFrom)
{

}
