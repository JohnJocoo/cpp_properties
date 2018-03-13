#include <gtest/gtest.h>

#include <prop/holding_property.hpp>

#include <string>
#include <atomic>
#include <utility>

#include "common.hpp"

class BasicHoldingProperties : prop::EnableProperties
{
public:
  BasicHoldingProperties()
    : int_value{ 0 }
    , ro_int_value{ 0 }
    , long_value{ 0 }
  {}
  
  BasicHoldingProperties& operator=( const BasicHoldingProperties& other )
  {
    int_value.ref() = other.int_value.cref();
    string_value.ref() = other.string_value.cref();
    ro_int_value.ref() = other.ro_int_value.cref();
    ro_string_value.ref() = other.ro_string_value.cref();
    string_value_b.ref() = other.string_value_b.cref();
    long_value.ref() = other.long_value.cref();
    string_holder.ref() = other.string_holder.cref();
    return *this;
  }

  template< typename Property >
  std::size_t getIndex()
  {
    return Property::Index;
  }
  
  void setIntValue( int value )
  {
    int_value.ref() = value;
  }
  
  void setStringValue( std::string value )
  {
    string_value.ref() = value;
  }
  
  void setROIntValue( int value )
  {
    ro_int_value.ref() = value;
  }
  
  void setROStringValue( std::string value )
  {
    ro_string_value.ref() = value;
  }
  
  void setROIntValueAssignment( int value )
  {
    ro_int_value = value;
  }
  
  void setROStringValueAssignment( std::string value )
  {
    ro_string_value = value;
  }

public:
  PROP_ENABLE_PROPERTIES( BasicHoldingProperties )
  PROP_HOLDING_PROPERTY( int, int_value, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( std::string, string_value, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( int, ro_int_value, prop::ReadOnly )
  PROP_HOLDING_PROPERTY( std::string, ro_string_value, prop::ReadOnly )
  
  PROP_HOLDING_PROPERTY( std::string, string_value_b, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( long long, long_value, prop::ReadWrite )
  
  PROP_HOLDING_PROPERTY( StringHolder, string_holder, prop::ReadWrite )
  
};

template < typename Property >
using OwnedByBasicHoldingProperties =
  std::is_same< typename Property::Owner, BasicHoldingProperties >;

template < typename Property >
using ValueIsInt =
  std::is_same< typename Property::ValueType, int >;

template < typename Property >
using ValueIsString =
  std::is_same< typename Property::ValueType, std::string >;

template < typename T >
using IsInt = std::is_same< T, int >;

template < typename T >
using IsString = std::is_same< T, std::string >;

template < typename T >
using IsConstIntRef = std::is_same< T, const int& >;

template < typename T >
using IsConstStringRef = std::is_same< T, const std::string& >;

template < typename Property >
using IsReadWrite =
  std::is_same< typename Property::Accessor, typename prop::ReadWrite >;

template < typename Property >
using IsReadOnly =
  std::is_same< typename Property::Accessor, typename prop::ReadOnly >;

TEST(HoldingProperty, Types)
{
  BasicHoldingProperties obj;

  EXPECT_TRUE( OwnedByBasicHoldingProperties< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( OwnedByBasicHoldingProperties< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( OwnedByBasicHoldingProperties< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( OwnedByBasicHoldingProperties< decltype( obj.ro_string_value ) >::value );
  
  EXPECT_TRUE( ValueIsInt< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( ValueIsInt< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.ro_string_value ) >::value );
  
  EXPECT_TRUE( IsReadWrite< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( IsReadOnly< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( IsReadOnly< decltype( obj.ro_string_value ) >::value );
  
  EXPECT_TRUE( IsConstIntRef< decltype( obj.int_value() ) >::value );
  EXPECT_TRUE( IsConstIntRef< decltype( obj.ro_int_value() ) >::value );
  EXPECT_TRUE( IsConstStringRef< decltype( obj.string_value() ) >::value );
  EXPECT_TRUE( IsConstStringRef< decltype( obj.ro_string_value() ) >::value );
  
  auto int_value = obj.int_value();
  auto ro_int_value = obj.ro_int_value();
  auto string_value = obj.string_value();
  auto ro_string_value = obj.ro_string_value();
  
  EXPECT_TRUE( IsInt< decltype( int_value ) >::value );
  EXPECT_TRUE( IsInt< decltype( ro_int_value ) >::value );
  EXPECT_TRUE( IsString< decltype( string_value ) >::value );
  EXPECT_TRUE( IsString< decltype( ro_string_value ) >::value );
}

TEST(HoldingProperty, Index)
{
  BasicHoldingProperties obj;
  
  EXPECT_EQ( 0, obj.getIndex< decltype( obj.int_value ) >() );
  EXPECT_EQ( 1, obj.getIndex< decltype( obj.string_value ) >() );
  EXPECT_EQ( 2, obj.getIndex< decltype( obj.ro_int_value ) >() );
  EXPECT_EQ( 3, obj.getIndex< decltype( obj.ro_string_value ) >() );
}

TEST(HoldingProperty, Traits)
{
  BasicHoldingProperties obj;
  
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.ro_string_value ) >::value );
  
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.int_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.ro_int_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.string_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.ro_string_value ) >::value );
  
  EXPECT_EQ( sizeof( int ), sizeof( obj.int_value ) );
  EXPECT_EQ( sizeof( int ), sizeof( obj.ro_int_value ) );
  EXPECT_EQ( sizeof( std::string ), sizeof( obj.string_value ) );
  EXPECT_EQ( sizeof( std::string ), sizeof( obj.ro_string_value ) );
}

TEST(HoldingProperty, GetOperator)
{
  BasicHoldingProperties obj;
  
  EXPECT_EQ( 0, obj.int_value() );
  EXPECT_EQ( 0, obj.ro_int_value() );
  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( "", obj.ro_string_value() );

  obj.setIntValue( 86 );
  obj.setStringValue( "bob" );
  obj.setROIntValue( 53 );
  obj.setROStringValue( "bill" );
  
  EXPECT_EQ( 86, obj.int_value() );
  EXPECT_EQ( 53, obj.ro_int_value() );
  EXPECT_EQ( "bob", obj.string_value() );
  EXPECT_EQ( "bill", obj.ro_string_value() );
}

TEST(HoldingProperty, GetConvertValue)
{
  BasicHoldingProperties obj;

  int int_value = obj.int_value;
  int ro_int_value = obj.ro_int_value;
  std::string string_value = obj.string_value;
  std::string ro_string_value = obj.ro_string_value;
  
  EXPECT_EQ( 0, int_value );
  EXPECT_EQ( 0, ro_int_value );
  EXPECT_EQ( "", string_value );
  EXPECT_EQ( "", ro_string_value );
  
  obj.setIntValue( 86 );
  obj.setStringValue( "bob" );
  obj.setROIntValue( 53 );
  obj.setROStringValue( "bill" );
  
  int_value = obj.int_value;
  ro_int_value = obj.ro_int_value;
  string_value = obj.string_value;
  ro_string_value = obj.ro_string_value;
  
  EXPECT_EQ( 86, int_value );
  EXPECT_EQ( 53, ro_int_value );
  EXPECT_EQ( "bob", string_value );
  EXPECT_EQ( "bill", ro_string_value );
  
  long long long_value = obj.int_value;
  long long ro_long_value = obj.ro_int_value;
  
  EXPECT_EQ( 86, long_value );
  EXPECT_EQ( 53, ro_long_value );
  
  StringHolder holder;
  holder = obj.string_value;
  EXPECT_EQ( "bob", holder.string );
}

TEST(HoldingProperty, GetConvertReference)
{
  BasicHoldingProperties obj;
  
  const int& int_value_cref = obj.int_value;
  const int& ro_int_value_cref = obj.ro_int_value;
  const std::string& string_value_cref = obj.string_value;
  const std::string& ro_string_value_cref = obj.ro_string_value;
  
  EXPECT_EQ( 0, int_value_cref );
  EXPECT_EQ( 0, ro_int_value_cref );
  EXPECT_EQ( "", string_value_cref );
  EXPECT_EQ( "", ro_string_value_cref );
  
  obj.setIntValue( 86 );
  obj.setStringValue( "bob" );
  obj.setROIntValue( 53 );
  obj.setROStringValue( "bill" );
  
  EXPECT_EQ( 86, int_value_cref );
  EXPECT_EQ( 53, ro_int_value_cref );
  EXPECT_EQ( "bob", string_value_cref );
  EXPECT_EQ( "bill", ro_string_value_cref );
  
  const long long& long_value_cref = obj.int_value;
  const long long& ro_long_value_cref = obj.ro_int_value;
  
  EXPECT_EQ( 86, long_value_cref );
  EXPECT_EQ( 53, ro_long_value_cref );
}

TEST(HoldingProperty, SetFromValue)
{
  BasicHoldingProperties obj;

  EXPECT_EQ( 0, obj.int_value() );
  EXPECT_EQ( 0, obj.ro_int_value() );
  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( "", obj.ro_string_value() );
  
  obj.int_value = 86;
  obj.string_value = std::string{ "bob" };
  obj.setROIntValueAssignment( 53 );
  obj.setROStringValueAssignment( "bill" );
  
  EXPECT_EQ( 86, obj.int_value() );
  EXPECT_EQ( 53, obj.ro_int_value() );
  EXPECT_EQ( "bob", obj.string_value() );
  EXPECT_EQ( "bill", obj.ro_string_value() );
  
  obj.int_value = (int8_t)24;
  obj.string_value = "john";
  
  EXPECT_EQ( 24, obj.int_value() );
  EXPECT_EQ( "john", obj.string_value() );
  
  obj.string_holder = "bob";
  EXPECT_EQ( "bob", obj.string_holder().string );
}

TEST(HoldingProperty, SetFromProperty)
{
  BasicHoldingProperties obj;

  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( "", obj.ro_string_value() );
  EXPECT_EQ( "", obj.string_value_b() );

  obj.setStringValue( "bill" );
  obj.setROStringValue( "bob" );
  obj.string_value_b = obj.string_value;
  obj.string_holder = obj.string_value;
  EXPECT_EQ( "bill", obj.string_value_b() );
  EXPECT_EQ( "bill", obj.string_value() );
  EXPECT_EQ( "bill", obj.string_holder().string );
  
  obj.string_value_b = obj.ro_string_value;
  obj.string_holder = obj.ro_string_value;
  EXPECT_EQ( "bob", obj.string_value_b() );
  EXPECT_EQ( "bob", obj.ro_string_value() );
  EXPECT_EQ( "bob", obj.string_holder().string );
  
  obj.setIntValue( 75 );
  obj.long_value = obj.int_value;
  EXPECT_EQ( 75, obj.int_value() );
  EXPECT_EQ( 75, obj.long_value() );
  
  obj.setROIntValue( 34 );
  obj.long_value = obj.ro_int_value;
  EXPECT_EQ( 34, obj.ro_int_value() );
  EXPECT_EQ( 34, obj.long_value() );
  
  BasicHoldingProperties obj2;
  obj2.setStringValue( "john" );
  obj2.setROStringValue( "kate" );
  obj2.setIntValue( 35 );
  obj2.setROIntValue( 84 );
  
  obj.string_value_b = obj2.string_value;
  obj.string_holder = obj2.string_value;
  obj.long_value = obj2.int_value;
  EXPECT_EQ( "john", obj.string_value_b() );
  EXPECT_EQ( "john", obj.string_holder().string );
  EXPECT_EQ( 35, obj.long_value() );
  
  obj.string_value_b = obj2.ro_string_value;
  obj.string_holder = obj2.ro_string_value;
  obj.long_value = obj2.ro_int_value;
  EXPECT_EQ( "kate", obj.string_value_b() );
  EXPECT_EQ( "kate", obj.string_holder().string );
  EXPECT_EQ( 84, obj.long_value() );
}

TEST(HoldingProperty, SetPiped)
{
  BasicHoldingProperties obj;

  EXPECT_EQ( 0, obj.int_value() );
  EXPECT_EQ( 0, obj.ro_int_value() );
  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( "", obj.ro_string_value() );
  EXPECT_EQ( "", obj.string_value_b() );
  
  obj.setROStringValue( "bill" );
  obj.string_value_b = obj.string_value = obj.ro_string_value;
  
  EXPECT_EQ( "bill", obj.ro_string_value() );
  EXPECT_EQ( "bill", obj.string_value() );
  EXPECT_EQ( "bill", obj.string_value_b() );
  
  obj.string_value_b = obj.string_value = "bob";
  
  EXPECT_EQ( "bob", obj.string_value() );
  EXPECT_EQ( "bob", obj.string_value_b() );
  
  obj.setROIntValue( 75 );
  obj.int_value = obj.long_value = obj.ro_int_value;
  
  EXPECT_EQ( 75, obj.ro_int_value );
  EXPECT_EQ( 75, obj.int_value );
  EXPECT_EQ( 75, obj.long_value );
  
  BasicHoldingProperties obj2;
  BasicHoldingProperties obj3;
  
  obj3.string_value = obj2.string_value = "john";
  
  EXPECT_EQ( "john", obj2.string_value() );
  EXPECT_EQ( "john", obj3.string_value() );
  
  obj.setStringValue( "kate" );
  obj3.string_value = obj2.string_value = obj.string_value;
  
  EXPECT_EQ( "kate", obj2.string_value() );
  EXPECT_EQ( "kate", obj3.string_value() );
  
  obj.setROStringValue( "jane" );
  obj3.string_value = obj2.string_value = obj.ro_string_value;
  
  EXPECT_EQ( "jane", obj2.string_value() );
  EXPECT_EQ( "jane", obj3.string_value() );
}

TEST(HoldingProperty, CopyOwner)
{
  BasicHoldingProperties obj_orig;
  obj_orig.int_value = 5;
  obj_orig.setROIntValue( 6 );
  obj_orig.string_value = "bob";
  obj_orig.setROStringValue( "bill" );
  
  BasicHoldingProperties obj{ obj_orig };
  EXPECT_EQ( 5, obj.int_value() );
  EXPECT_EQ( 6, obj.ro_int_value() );
  EXPECT_EQ( "bob", obj.string_value() );
  EXPECT_EQ( "bill", obj.ro_string_value() );
  
  BasicHoldingProperties obj2;
  obj2.int_value = 0;
  obj2.string_value = "";
  obj2 = obj_orig;
  EXPECT_EQ( 5, obj2.int_value() );
  EXPECT_EQ( 6, obj2.ro_int_value() );
  EXPECT_EQ( "bob", obj2.string_value() );
  EXPECT_EQ( "bill", obj2.ro_string_value() );
}

class HoldingMovableType : prop::EnableProperties
{
public:
  HoldingMovableType() = default;
  HoldingMovableType( const HoldingMovableType& ) = default;
  HoldingMovableType( HoldingMovableType&& ) = default;

  HoldingMovableType& operator=( const HoldingMovableType& other )
  {
    value1 = other.value1;
    value2 = other.value2;
    value3 = other.value3;
    ro_value = other.ro_value;
    ro_value2 = other.ro_value2;
    return *this;
  }
  
  HoldingMovableType& operator=( HoldingMovableType&& other )
  {
    value1 = std::move( other.value1 );
    value2 = std::move( other.value2 );
    value3 = std::move( other.value3 );
    ro_value = std::move( other.ro_value );
    ro_value2 = std::move( other.ro_value2 );
    return *this;
  }

  PROP_ENABLE_PROPERTIES( HoldingMovableType )
  PROP_HOLDING_PROPERTY( Movable, value1, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( Movable, value2, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( Movable, ro_value, prop::ReadOnly )
  
  PROP_HOLDING_PROPERTY( IdHolder, value3, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( IdHolder, ro_value2, prop::ReadOnly )

};

/*
 * Generally moving to and from
 * is very well supported by holding
 * property. Even moving from ReadOnly
 * property is possible.
 * The only limitation is that you can not
 * move from returned value of operator().
 */

TEST(HoldingProperty, MoveTo)
{
  HoldingMovableType obj;
  Movable move_from;
  auto remembered_value = move_from.getId();
  obj.value1 = std::move( move_from );
  EXPECT_EQ( remembered_value, obj.value1().getId() );
  EXPECT_EQ( 0, move_from.getId() );
  
  IdHolder move_from_other;
  remembered_value = move_from_other.id;
  obj.value1 = std::move( move_from_other );
  EXPECT_EQ( remembered_value, obj.value1().getId() );
  EXPECT_EQ( 0, move_from_other.id );
}

TEST(HoldingProperty, MoveProp)
{
  HoldingMovableType obj;
  auto remembered_value = obj.value1().getId();
  obj.value2 = std::move( obj.value1 );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj.value1().getId() );
  
  remembered_value = obj.value3().id;
  obj.value2 = std::move( obj.value3 );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj.value3().id );
  
  remembered_value = obj.ro_value().getId();
  obj.value2 = std::move( obj.ro_value );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj.ro_value().getId() );
  
  remembered_value = obj.ro_value2().id;
  obj.value2 = std::move( obj.ro_value2 );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj.ro_value2().id );
  
  HoldingMovableType obj2;
  remembered_value = obj2.value1().getId();
  obj.value2 = std::move( obj2.value1 );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj2.value1().getId() );
  
  remembered_value = obj2.value3().id;
  obj.value2 = std::move( obj2.value3 );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj2.value3().id );
  
  remembered_value = obj2.ro_value().getId();
  obj.value2 = std::move( obj2.ro_value );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj2.ro_value().getId() );
  
  remembered_value = obj2.ro_value2().id;
  obj.value2 = std::move( obj2.ro_value2 );
  EXPECT_EQ( remembered_value, obj.value2().getId() );
  EXPECT_EQ( 0, obj2.ro_value2().id );
}

TEST(HoldingProperty, MoveFrom)
{
  HoldingMovableType obj;

  // can't move from returned value
  auto remembered_value = obj.value1().getId();
  Movable move_to = std::move( obj.value1() );
  EXPECT_NE( remembered_value, move_to.getId() );
  EXPECT_NE( 0, obj.value1().getId() );
  
  // can't move from returned value
  remembered_value = obj.ro_value().getId();
  Movable move_to4 = std::move( obj.ro_value() );
  EXPECT_NE( remembered_value, move_to4.getId() );
  EXPECT_NE( 0, obj.ro_value().getId() );
  
#if MOVE_CAST_SUPPORTED

  remembered_value = obj.value1().getId();
  Movable move_to2 = std::move( obj.value1 );
  EXPECT_EQ( remembered_value, move_to2.getId() );
  EXPECT_EQ( 0, obj.value1().getId() );
  
  remembered_value = obj.ro_value().getId();
  Movable move_to3 = std::move( obj.ro_value );
  EXPECT_EQ( remembered_value, move_to3.getId() );
  EXPECT_EQ( 0, obj.ro_value().getId() );

#else

  remembered_value = obj.value1().getId();
  Movable move_to2 = std::move( obj.value1 );
  EXPECT_NE( remembered_value, move_to2.getId() );
  EXPECT_NE( 0, obj.value1().getId() );

  remembered_value = obj.ro_value().getId();
  Movable move_to3 = std::move( obj.ro_value );
  EXPECT_NE( remembered_value, move_to3.getId() );
  EXPECT_NE( 0, obj.ro_value().getId() );

#endif
}

#if CAN_MOVE_CASTABLE

TEST( HoldingProperty, MoveFromCastable )
{
  HoldingMovableType obj;

  auto remembered_value = obj.value3().id;
  Movable move_to5;
  move_to5 = std::move( obj.value3 );
  EXPECT_EQ( remembered_value, move_to5.getId() );
  EXPECT_EQ( 0, obj.value3().id );

  remembered_value = obj.ro_value2().id;
  Movable move_to6;
  move_to6 = std::move( obj.ro_value2 );
  EXPECT_EQ( remembered_value, move_to6.getId() );
  EXPECT_EQ( 0, obj.ro_value2().id );
}

#endif

TEST(HoldingProperty, MoveOwner)
{
  HoldingMovableType obj;

  auto remembered_value = obj.value1().getId();
  HoldingMovableType copy_to{ obj };
  EXPECT_NE( remembered_value, copy_to.value1().getId() );
  EXPECT_NE( 0, obj.value1().getId() );
  
  HoldingMovableType move_to{ std::move( obj ) };
  EXPECT_EQ( remembered_value, move_to.value1().getId() );
  EXPECT_EQ( 0, obj.value1().getId() );
  
  HoldingMovableType obj2;
  
  remembered_value = obj2.value1().getId();
  copy_to = obj2;
  EXPECT_NE( remembered_value, copy_to.value1().getId() );
  EXPECT_NE( 0, obj2.value1().getId() );
  
  move_to = std::move( obj2 );
  EXPECT_EQ( remembered_value, move_to.value1().getId() );
  EXPECT_EQ( 0, obj2.value1().getId() );
}
