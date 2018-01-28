#include <gtest/gtest.h>

#include <prop/method_property.hpp>

#include "common.hpp"

class BasicMethodProperties : prop::EnableProperties
{
public:
  BasicMethodProperties() = default;
  BasicMethodProperties( const BasicMethodProperties& ) = default;
  ~BasicMethodProperties() = default;
  
  BasicMethodProperties& operator=( const BasicMethodProperties& other )
  {
    m_int_value = other.m_int_value;
    m_string_value = other.m_string_value;
    m_int_value2 = other.m_int_value2;
    m_string_value2 = other.m_string_value2;
    m_string_holder = other.m_string_holder;
    m_long_value = other.m_long_value;
    return *this;
  }
  
  int& getIntValueTest()
  {
    return m_int_value;
  }
  
  std::string& getStringValueTest()
  {
    return m_string_value;
  }
  
  int& getIntValue2Test()
  {
    return m_int_value2;
  }
  
  std::string& getStringValue2Test()
  {
    return m_string_value2;
  }
  
  template< typename Property >
  std::size_t getIndex()
  {
    return Property::Index;
  }
  
private:
    int getIntValue() const
    {
      return m_int_value;
    }
  
    const int& getIntValueCRef() const
    {
      return m_int_value;
    }
  
    std::string getStringValue() const
    {
      return m_string_value;
    }
  
    const std::string& getStringValueCRef() const
    {
      return m_string_value;
    }
  
    int getIntValue2() const
    {
      return m_int_value2;
    }
  
    int getIntValue2_() const
    {
      return m_int_value2;
    }
  
    const int& getIntValue2CRef() const
    {
      return m_int_value2;
    }
  
    std::string getStringValue2() const
    {
      return m_string_value2;
    }
  
    std::string getStringValue2_() const
    {
      return m_string_value2;
    }
  
    const std::string& getStringValue2CRef() const
    {
      return m_string_value2;
    }
  
    void setIntValue2( int value )
    {
      m_int_value2 = value;
    }
  
    void setIntValue2CRef( const int& value )
    {
      m_int_value2 = value;
    }
  
    void setIntValue2RVRef( int&& value )
    {
      m_int_value2 = value;
    }
  
    void setStringValue2( std::string value )
    {
      m_string_value2 = std::move( value );
    }
  
    void setStringValue2CRef( const std::string& value )
    {
      m_string_value2 = value;
    }
  
    void setStringValue2RVRef( std::string&& value )
    {
      m_string_value2 = std::move( value );
    }
  
    StringHolder getStringHolder() const
    {
      return m_string_holder;
    }
  
    StringHolder getStringHolder_() const
    {
      return m_string_holder;
    }
  
    const StringHolder& getStringHolderCRef() const
    {
      return m_string_holder;
    }
  
    void setStringHolder( StringHolder value )
    {
      m_string_holder = std::move( value );
    }
  
    void setStringHolderCRef( const StringHolder& value )
    {
      m_string_holder = value;
    }
  
    void setStringHolderRVRef( StringHolder&& value )
    {
      m_string_holder = std::move( value );
    }
  
    long long getLongValue() const
    {
      return m_long_value;
    }
  
    void setLongValue( long long value )
    {
      m_long_value = value;
    }

private:
  int m_int_value = 0;
  std::string m_string_value;
  int m_int_value2 = 0;
  std::string m_string_value2;
  StringHolder m_string_holder;
  long long m_long_value = 0;
  
public:
  PROP_ENABLE_PROPERTIES( BasicMethodProperties )
  PROP_DETAIL_METHOD_PROPERTY_GET_33fe95a2(int, ro_int_value, getIntValue)
  PROP_DETAIL_METHOD_PROPERTY_GET_33fe95a2(int, ro_int_value2, getIntValueCRef)
  PROP_DETAIL_METHOD_PROPERTY_GET_33fe95a2(std::string, ro_string_value, getStringValue)
  PROP_DETAIL_METHOD_PROPERTY_GET_33fe95a2(std::string, ro_string_value2, getStringValueCRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(int, int_value, getIntValue2, setIntValue2)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(int, int_value2, getIntValue2CRef, setIntValue2CRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(int, int_value3, getIntValue2_, setIntValue2RVRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(std::string, string_value, getStringValue2, setStringValue2)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(std::string, string_value2, getStringValue2CRef, setStringValue2CRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(std::string, string_value3, getStringValue2_, setStringValue2RVRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(StringHolder, string_holder, getStringHolder, setStringHolder)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(StringHolder, string_holder2, getStringHolderCRef, setStringHolderCRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(StringHolder, string_holder3, getStringHolder_, setStringHolderRVRef)
  PROP_DETAIL_METHOD_PROPERTY_SET_33fe95a2(long long, long_value, getLongValue, setLongValue);

}; // class BasicMethodProperties

template < typename Property >
using OwnedByBasicMethodProperties =
  std::is_same< typename Property::Owner, BasicMethodProperties >;

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

TEST(MethodProperty, Types)
{
  BasicMethodProperties obj;

  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.ro_string_value ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.ro_int_value2 ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.ro_string_value2 ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.int_value2 ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.string_value2 ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.int_value3 ) >::value );
  EXPECT_TRUE( OwnedByBasicMethodProperties< decltype( obj.string_value3 ) >::value );
  
  EXPECT_TRUE( ValueIsInt< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( ValueIsInt< decltype( obj.ro_int_value2 ) >::value );
  EXPECT_TRUE( ValueIsInt< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( ValueIsInt< decltype( obj.int_value2 ) >::value );
  EXPECT_TRUE( ValueIsInt< decltype( obj.int_value3 ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.ro_string_value ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.ro_string_value2 ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.string_value2 ) >::value );
  EXPECT_TRUE( ValueIsString< decltype( obj.string_value3 ) >::value );
  
  EXPECT_TRUE( IsReadOnly< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( IsReadOnly< decltype( obj.ro_string_value ) >::value );
  EXPECT_TRUE( IsReadOnly< decltype( obj.ro_int_value2 ) >::value );
  EXPECT_TRUE( IsReadOnly< decltype( obj.ro_string_value2 ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.int_value2 ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.string_value2 ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.int_value3 ) >::value );
  EXPECT_TRUE( IsReadWrite< decltype( obj.string_value3 ) >::value );
  
  EXPECT_TRUE( IsInt< decltype( obj.ro_int_value() ) >::value );
  EXPECT_TRUE( IsInt< decltype( obj.ro_int_value2() ) >::value );
  EXPECT_TRUE( IsInt< decltype( obj.int_value() ) >::value );
  EXPECT_TRUE( IsInt< decltype( obj.int_value2() ) >::value );
  EXPECT_TRUE( IsInt< decltype( obj.int_value3() ) >::value );
  EXPECT_TRUE( IsString< decltype( obj.ro_string_value() ) >::value );
  EXPECT_TRUE( IsString< decltype( obj.ro_string_value2() ) >::value );
  EXPECT_TRUE( IsString< decltype( obj.string_value() ) >::value );
  EXPECT_TRUE( IsString< decltype( obj.string_value2() ) >::value );
  EXPECT_TRUE( IsString< decltype( obj.string_value3() ) >::value );
  
  auto ro_int_value = obj.ro_int_value();
  auto ro_int_value2 = obj.ro_int_value2();
  auto int_value = obj.int_value();
  auto int_value2 = obj.int_value2();
  auto int_value3 = obj.int_value3();
  auto ro_string_value = obj.ro_string_value();
  auto ro_string_value2 = obj.ro_string_value2();
  auto string_value = obj.string_value();
  auto string_value2 = obj.string_value2();
  auto string_value3 = obj.string_value3();
  
  EXPECT_TRUE( IsInt< decltype( ro_int_value ) >::value );
  EXPECT_TRUE( IsInt< decltype( ro_int_value2 ) >::value );
  EXPECT_TRUE( IsInt< decltype( int_value ) >::value );
  EXPECT_TRUE( IsInt< decltype( int_value2 ) >::value );
  EXPECT_TRUE( IsInt< decltype( int_value3 ) >::value );
  EXPECT_TRUE( IsString< decltype( ro_string_value ) >::value );
  EXPECT_TRUE( IsString< decltype( ro_string_value2 ) >::value );
  EXPECT_TRUE( IsString< decltype( string_value ) >::value );
  EXPECT_TRUE( IsString< decltype( string_value2 ) >::value );
  EXPECT_TRUE( IsString< decltype( string_value3 ) >::value );
}

TEST(MethodProperty, Index)
{
  BasicMethodProperties obj;
  
  EXPECT_EQ( 0, obj.getIndex< decltype( obj.ro_int_value ) >() );
  EXPECT_EQ( 1, obj.getIndex< decltype( obj.ro_int_value2 ) >() );
  EXPECT_EQ( 2, obj.getIndex< decltype( obj.ro_string_value ) >() );
  EXPECT_EQ( 3, obj.getIndex< decltype( obj.ro_string_value2 ) >() );
  EXPECT_EQ( 4, obj.getIndex< decltype( obj.int_value ) >() );
  EXPECT_EQ( 5, obj.getIndex< decltype( obj.int_value2 ) >() );
  EXPECT_EQ( 6, obj.getIndex< decltype( obj.int_value3 ) >() );
  EXPECT_EQ( 7, obj.getIndex< decltype( obj.string_value ) >() );
  EXPECT_EQ( 8, obj.getIndex< decltype( obj.string_value2 ) >() );
  EXPECT_EQ( 9, obj.getIndex< decltype( obj.string_value3 ) >() );
}

TEST(MethodProperty, Traits)
{
  BasicMethodProperties obj;
  
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.ro_int_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.ro_int_value2 ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.int_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.int_value2 ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.int_value3 ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.ro_string_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.ro_string_value2 ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.string_value ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.string_value2 ) >::value );
  EXPECT_TRUE( prop::detail::IsProperty< decltype( obj.string_value3 ) >::value );
  
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.ro_int_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.ro_int_value2 ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.int_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.int_value2 ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.int_value3 ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.ro_string_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.ro_string_value2 ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.string_value ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.string_value2 ) >::value );
  EXPECT_FALSE( prop::detail::IsAliasProperty< decltype( obj.string_value3 ) >::value );
  
  EXPECT_EQ( sizeof( char ), sizeof( obj.ro_int_value ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.ro_int_value2 ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.int_value ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.int_value2 ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.int_value3 ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.ro_string_value ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.ro_string_value2 ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.string_value ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.string_value2 ) );
  EXPECT_EQ( sizeof( char ), sizeof( obj.string_value3 ) );
}

TEST(MethodProperty, GetOperator)
{
  BasicMethodProperties obj;
  
  EXPECT_EQ( 0, obj.ro_int_value() );
  EXPECT_EQ( 0, obj.ro_int_value2() );
  EXPECT_EQ( 0, obj.int_value() );
  EXPECT_EQ( 0, obj.int_value2() );
  EXPECT_EQ( 0, obj.int_value3() );
  EXPECT_EQ( "", obj.ro_string_value() );
  EXPECT_EQ( "", obj.ro_string_value2() );
  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( "", obj.string_value2() );
  EXPECT_EQ( "", obj.string_value3() );

  obj.getIntValueTest() = 86;
  obj.getStringValueTest() = "bob";
  obj.getIntValue2Test() = 34;
  obj.getStringValue2Test() = "bill";
  
  EXPECT_EQ( 86, obj.ro_int_value() );
  EXPECT_EQ( 86, obj.ro_int_value2() );
  EXPECT_EQ( 34, obj.int_value() );
  EXPECT_EQ( 34, obj.int_value2() );
  EXPECT_EQ( 34, obj.int_value3() );
  EXPECT_EQ( "bob", obj.ro_string_value() );
  EXPECT_EQ( "bob", obj.ro_string_value2() );
  EXPECT_EQ( "bill", obj.string_value() );
  EXPECT_EQ( "bill", obj.string_value2() );
  EXPECT_EQ( "bill", obj.string_value3() );
}

TEST(MethodProperty, GetConvertValue)
{
  BasicMethodProperties obj;

  int ro_int_value = obj.ro_int_value;
  int ro_int_value2 = obj.ro_int_value2;
  int int_value = obj.int_value;
  int int_value2 = obj.int_value2;
  int int_value3 = obj.int_value3;
  std::string ro_string_value = obj.ro_string_value;
  std::string ro_string_value2 = obj.ro_string_value2;
  std::string string_value = obj.string_value;
  std::string string_value2 = obj.string_value2;
  std::string string_value3 = obj.string_value3;
  
  EXPECT_EQ( 0, ro_int_value );
  EXPECT_EQ( 0, ro_int_value2 );
  EXPECT_EQ( 0, int_value );
  EXPECT_EQ( 0, int_value2 );
  EXPECT_EQ( 0, int_value3 );
  EXPECT_EQ( "", ro_string_value );
  EXPECT_EQ( "", ro_string_value2 );
  EXPECT_EQ( "", string_value );
  EXPECT_EQ( "", string_value2 );
  EXPECT_EQ( "", string_value3 );
  
  obj.getIntValueTest() = 86;
  obj.getStringValueTest() = "bob";
  obj.getIntValue2Test() = 53;
  obj.getStringValue2Test() = "bill";
  
  ro_int_value = obj.ro_int_value;
  ro_int_value2 = obj.ro_int_value2;
  int_value = obj.int_value;
  int_value2 = obj.int_value2;
  int_value3 = obj.int_value3;
  ro_string_value = obj.ro_string_value;
  ro_string_value2 = obj.ro_string_value2;
  string_value = obj.string_value;
  string_value2 = obj.string_value2;
  string_value3 = obj.string_value3;
  
  EXPECT_EQ( 86, ro_int_value );
  EXPECT_EQ( 86, ro_int_value2 );
  EXPECT_EQ( 53, int_value );
  EXPECT_EQ( 53, int_value2 );
  EXPECT_EQ( 53, int_value3 );
  EXPECT_EQ( "bob", ro_string_value );
  EXPECT_EQ( "bob", ro_string_value2 );
  EXPECT_EQ( "bill", string_value );
  EXPECT_EQ( "bill", string_value2 );
  EXPECT_EQ( "bill", string_value3 );
  
  long long ro_long_value = obj.ro_int_value;
  long long ro_long_value2 = obj.ro_int_value2;
  long long long_value = obj.int_value;
  long long long_value2 = obj.int_value2;
  long long long_value3 = obj.int_value3;
  
  EXPECT_EQ( 86, ro_long_value );
  EXPECT_EQ( 86, ro_long_value2 );
  EXPECT_EQ( 53, long_value );
  EXPECT_EQ( 53, long_value2 );
  EXPECT_EQ( 53, long_value3 );
  
  StringHolder holder;
  StringHolder holder2;
  StringHolder holder3;
  StringHolder holder4;
  StringHolder holder5;
  holder = obj.ro_string_value;
  holder2 = obj.ro_string_value2;
  holder3 = obj.string_value;
  holder4 = obj.string_value2;
  holder5 = obj.string_value3;
  EXPECT_EQ( "bob", holder.string );
  EXPECT_EQ( "bob", holder2.string );
  EXPECT_EQ( "bill", holder3.string );
  EXPECT_EQ( "bill", holder4.string );
  EXPECT_EQ( "bill", holder5.string );
}

TEST(MethodProperty, GetConvertReference)
{
  BasicMethodProperties obj;
  
  const int& ro_int_value_cref = obj.ro_int_value;
  const int& ro_int_value_cref2 = obj.ro_int_value2;
  const int& int_value_cref = obj.int_value;
  const int& int_value_cref2 = obj.int_value2;
  const int& int_value_cref3 = obj.int_value3;
  const std::string& ro_string_value_cref = obj.ro_string_value;
  const std::string& ro_string_value_cref2 = obj.ro_string_value2;
  const std::string& string_value_cref = obj.string_value;
  const std::string& string_value_cref2 = obj.string_value2;
  const std::string& string_value_cref3 = obj.string_value3;
  
  EXPECT_EQ( 0, ro_int_value_cref );
  EXPECT_EQ( 0, ro_int_value_cref2 );
  EXPECT_EQ( 0, int_value_cref );
  EXPECT_EQ( 0, int_value_cref2 );
  EXPECT_EQ( 0, int_value_cref3 );
  EXPECT_EQ( "", ro_string_value_cref );
  EXPECT_EQ( "", ro_string_value_cref2 );
  EXPECT_EQ( "", string_value_cref );
  EXPECT_EQ( "", string_value_cref2 );
  EXPECT_EQ( "", string_value_cref3 );
  
  obj.getIntValueTest() = 86;
  obj.getStringValueTest() = "bob";
  obj.getIntValue2Test() = 74;
  obj.getStringValue2Test() = "bill";
  
  EXPECT_EQ( 0, ro_int_value_cref );
  EXPECT_EQ( 0, ro_int_value_cref2 );
  EXPECT_EQ( 0, int_value_cref );
  EXPECT_EQ( 0, int_value_cref2 );
  EXPECT_EQ( 0, int_value_cref3 );
  EXPECT_EQ( "", ro_string_value_cref );
  EXPECT_EQ( "", ro_string_value_cref2 );
  EXPECT_EQ( "", string_value_cref );
  EXPECT_EQ( "", string_value_cref2 );
  EXPECT_EQ( "", string_value_cref3 );
  
  const long long& ro_long_value_cref = obj.ro_int_value;
  const long long& ro_long_value_cref2 = obj.ro_int_value2;
  const long long& long_value_cref = obj.int_value;
  const long long& long_value_cref2 = obj.int_value2;
  const long long& long_value_cref3 = obj.int_value3;
  
  EXPECT_EQ( 86, ro_long_value_cref );
  EXPECT_EQ( 86, ro_long_value_cref2 );
  EXPECT_EQ( 74, long_value_cref );
  EXPECT_EQ( 74, long_value_cref2 );
  EXPECT_EQ( 74, long_value_cref3 );
}

TEST(MethodProperty, SetFromValue)
{
  BasicMethodProperties obj;

  EXPECT_EQ( 0, obj.int_value() );
  EXPECT_EQ( 0, obj.int_value2() );
  EXPECT_EQ( 0, obj.int_value3() );
  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( "", obj.string_value2() );
  EXPECT_EQ( "", obj.string_value3() );
  
  obj.int_value = 86;
  obj.string_value = std::string{ "bob" };
  EXPECT_EQ( 86, obj.int_value() );
  EXPECT_EQ( "bob", obj.string_value() );
  
  obj.int_value2 = 34;
  obj.string_value2 = std::string{ "bill" };
  EXPECT_EQ( 34, obj.int_value2() );
  EXPECT_EQ( "bill", obj.string_value2() );
  
  obj.int_value3 = 98;
  obj.string_value3 = std::string{ "john" };
  EXPECT_EQ( 98, obj.int_value3() );
  EXPECT_EQ( "john", obj.string_value3() );
  
  obj.int_value = (int8_t)24;
  obj.string_value = "paul";
  EXPECT_EQ( 24, obj.int_value() );
  EXPECT_EQ( "paul", obj.string_value() );
  
  obj.int_value = (int8_t)64;
  obj.string_value = "rob";
  EXPECT_EQ( 64, obj.int_value() );
  EXPECT_EQ( "rob", obj.string_value() );
  
  obj.int_value = (int8_t)56;
  obj.string_value = "greg";
  EXPECT_EQ( 56, obj.int_value() );
  EXPECT_EQ( "greg", obj.string_value() );
  
  obj.string_holder = "bob";
  EXPECT_EQ( "bob", obj.string_holder().string );
  
  obj.string_holder2 = "bill";
  EXPECT_EQ( "bill", obj.string_holder2().string );
  
  obj.string_holder3 = "john";
  EXPECT_EQ( "john", obj.string_holder3().string );
}

TEST(MethodProperty, SetFromProperty)
{
  BasicMethodProperties obj;
  BasicMethodProperties obj2;

  EXPECT_EQ( "", obj.string_value() );
  EXPECT_EQ( 0, obj.int_value() );
  EXPECT_EQ( "", obj.string_value2() );
  EXPECT_EQ( 0, obj.int_value2() );
  EXPECT_EQ( "", obj.string_value3() );
  EXPECT_EQ( 0, obj.int_value3() );
  EXPECT_EQ( 0, obj.long_value() );

  obj2.getIntValue2Test() = 65;
  obj2.getStringValue2Test() = "bob";
  obj.string_value = obj2.string_value;
  obj.int_value = obj2.int_value;
  EXPECT_EQ( "bob", obj.string_value() );
  EXPECT_EQ( 65, obj.int_value() );
  
  obj2.getIntValue2Test() = 23;
  obj2.getStringValue2Test() = "bill";
  obj.string_value = obj2.string_value2;
  obj.int_value = obj2.int_value2;
  EXPECT_EQ( "bill", obj.string_value() );
  EXPECT_EQ( 23, obj.int_value() );
  
  obj2.getIntValueTest() = 72;
  obj2.getStringValueTest() = "john";
  obj.string_value = obj2.ro_string_value;
  obj.int_value = obj2.ro_int_value;
  EXPECT_EQ( "john", obj.string_value() );
  EXPECT_EQ( 72, obj.int_value() );
  
  obj2.getIntValueTest() = 14;
  obj2.getStringValueTest() = "kate";
  obj.string_value2 = obj2.ro_string_value;
  obj.int_value2 = obj2.ro_int_value;
  EXPECT_EQ( "kate", obj.string_value2() );
  EXPECT_EQ( 14, obj.int_value2() );
  
  obj2.getIntValueTest() = 97;
  obj2.getStringValueTest() = "jane";
  obj.string_value3 = obj2.ro_string_value;
  obj.int_value3 = obj2.ro_int_value;
  EXPECT_EQ( "jane", obj.string_value3() );
  EXPECT_EQ( 97, obj.int_value3() );
  
  obj2.getIntValue2Test() = 19;
  obj2.getStringValue2Test() = "greg";
  obj.string_holder = obj2.string_value;
  obj.long_value = obj2.int_value;
  EXPECT_EQ( "greg", obj.string_holder().string );
  EXPECT_EQ( 19, obj.long_value() );
  
  obj2.getIntValueTest() = 51;
  obj2.getStringValueTest() = "phill";
  obj.string_holder = obj2.ro_string_value;
  obj.long_value = obj2.ro_int_value;
  EXPECT_EQ( "phill", obj.string_holder().string );
  EXPECT_EQ( 51, obj.long_value() );
  
  obj2.getStringValue2Test() = "matt";
  obj.string_holder2 = obj2.string_value;
  EXPECT_EQ( "matt", obj.string_holder().string );
  
  obj2.getStringValue2Test() = "sam";
  obj.string_holder3 = obj2.string_value;
  EXPECT_EQ( "sam", obj.string_holder().string );
}

TEST(MethodProperty, SetPiped)
{
  BasicMethodProperties obj;
  BasicMethodProperties obj2;
  BasicMethodProperties obj3;
  
  obj3.string_value = obj2.string_value = "john";
  
  EXPECT_EQ( "john", obj2.string_value() );
  EXPECT_EQ( "john", obj3.string_value() );
  
  obj.getStringValue2Test() = "kate";
  obj3.string_value = obj2.string_value = obj.string_value;
  
  EXPECT_EQ( "kate", obj2.string_value() );
  EXPECT_EQ( "kate", obj3.string_value() );
  
  obj.getStringValue2Test() = "bob";
  obj3.string_value3 = obj2.string_value2 = obj.string_value;
  
  EXPECT_EQ( "bob", obj2.string_value2() );
  EXPECT_EQ( "bob", obj3.string_value3() );
  
  obj.getStringValueTest() = "jane";
  obj3.string_value2 = obj2.string_value = obj.ro_string_value;
  
  EXPECT_EQ( "jane", obj2.string_value() );
  EXPECT_EQ( "jane", obj3.string_value2() );

  obj3.int_value = obj2.long_value = 24;
  EXPECT_EQ( 24, obj2.long_value() );
  EXPECT_EQ( 24, obj3.int_value() );
  
  obj3.int_value2 = obj2.long_value = 71;
  EXPECT_EQ( 71, obj2.long_value() );
  EXPECT_EQ( 71, obj3.int_value2() );
  
  obj3.int_value3 = obj2.long_value = 54;
  EXPECT_EQ( 54, obj2.long_value() );
  EXPECT_EQ( 54, obj3.int_value3() );

  obj.getIntValueTest() = 75;
  obj3.int_value = obj2.long_value = obj.ro_int_value;
  EXPECT_EQ( 75, obj2.long_value() );
  EXPECT_EQ( 75, obj3.int_value3() );
}

TEST(MethodProperty, CopyOwner)
{
  BasicMethodProperties obj_orig;
  obj_orig.getIntValue2Test() = 5;
  obj_orig.getIntValueTest() = 6;
  obj_orig.getStringValue2Test() = "bob";
  obj_orig.getStringValueTest() = "bill";
  
  BasicMethodProperties obj{ obj_orig };
  EXPECT_EQ( 5, obj.int_value() );
  EXPECT_EQ( 6, obj.ro_int_value() );
  EXPECT_EQ( "bob", obj.string_value() );
  EXPECT_EQ( "bill", obj.ro_string_value() );
  
  BasicMethodProperties obj2;
  obj2.int_value = 0;
  obj2.string_value = "";
  obj2 = obj_orig;
  EXPECT_EQ( 5, obj2.int_value() );
  EXPECT_EQ( 6, obj2.ro_int_value() );
  EXPECT_EQ( "bob", obj2.string_value() );
  EXPECT_EQ( "bill", obj2.ro_string_value() );
}
