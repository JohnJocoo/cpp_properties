#pragma once

#include <string>
#include <atomic>

#if defined _MSC_VER
# if _MSC_VER >= 1910 
#   define MOVE_CAST_SUPPORTED 1
#   define CAN_MOVE_CASTABLE 1
# else
#   define MOVE_CAST_SUPPORTED 0
#   define CAN_MOVE_CASTABLE 0
# endif
#else
#   define MOVE_CAST_SUPPORTED 1
# define CAN_MOVE_CASTABLE 1
#endif

namespace
{

int getUID()
{
  static std::atomic_int _uid_gen{ 0 };
  return ++_uid_gen;
}

}

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

class IdHolder
{
public:
    IdHolder()
    : id{ getUID() }
  {}
  
  int id;
};

class Movable
{
public:
  Movable()
    : m_id{ getUID() }
  {}
  
  Movable( const Movable& other )
    : m_id{ getUID() }
  {}
  
  Movable( Movable&& other )
    : m_id{ other.m_id }
  {
    other.m_id = 0;
  }
  
  Movable( const IdHolder& other )
    : m_id{ getUID() }
  {}
  
  Movable( IdHolder&& other )
    : m_id{ other.id }
  {
    other.id = 0;
  }
  
  ~Movable() = default;
  
  Movable& operator=( const Movable& other )
  {
    m_id = getUID();
    return *this;
  }
  
  Movable& operator=( Movable&& other )
  {
    m_id = other.m_id;
    other.m_id = 0;
    return *this;
  }
  
  Movable& operator=( const IdHolder& other )
  {
    m_id = getUID();
    return *this;
  }
  
  Movable& operator=( IdHolder&& other )
  {
    m_id = other.id;
    other.id = 0;
    return *this;
  }
  
  int getId() const
  {
    return m_id;
  }
  
private:
  int m_id;
  
};
