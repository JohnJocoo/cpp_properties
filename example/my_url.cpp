#include <string>
#include <iostream> 
#include <sstream>

#include <prop/properties.hpp>
  
std::string toURL( const std::string& host, int port, const std::string& path,
  const std::string& user_name, const std::string& user_secret );
void printLine( const std::string& line );

struct User
{
  std::string name;
  std::string secret;

}; // struct User

class OriginalResource
{
public:
  OriginalResource() = default;
  OriginalResource( const std::string& host )
    : m_host{ host }
    , m_port{ 0 }
  {}

  const std::string& getHost() const
  {
    return m_host;
  }

  int getPort() const
  {
    return m_port;
  }

  void setPort( int port )
  {
    m_port = port;
  }

  const std::string& getPath() const
  {
    return m_path;
  }

  void setPath( const std::string& path )
  {
    m_path = path;
  }

  User getUser() const
  {
    return { m_userName, m_userSecret };
  }

  void setUser( const User& user )
  {
    m_userName = user.name;
    m_userSecret = user.secret;
  }

  std::string getURL() const
  {
    return toURL( m_host, m_port, m_path, m_userName, m_userSecret );
  }

private:
  std::string m_host;
  int m_port;
  std::string m_path;
  std::string m_userName;
  std::string m_userSecret;

}; // class OriginalResource

class PropertyResource : prop::EnableProperties
{
public:
  PropertyResource() = default;
  PropertyResource( const std::string& host )
    : host{ host }
    , port{ 0 }
  {}

private:
  User getUser() const
  {
    return{ m_userName, m_userSecret };
  }

  void setUser( const User& user )
  {
    m_userName = user.name;
    m_userSecret = user.secret;
  }

  std::string getURL() const
  {
    return toURL( host, port, path, m_userName, m_userSecret );
  }

private:
  std::string m_userName;
  std::string m_userSecret;

public:
  PROP_ENABLE_PROPERTIES( PropertyResource )
  PROP_HOLDING_PROPERTY( std::string, host, prop::ReadOnly )
  PROP_HOLDING_PROPERTY( int, port, prop::ReadWrite )
  PROP_HOLDING_PROPERTY( std::string, path, prop::ReadWrite )
  PROP_METHOD_PROPERTY( User, user, getUser, setUser, prop::ReadWrite )
  PROP_METHOD_PROPERTY( std::string, URL, getURL, prop::ReadOnly )

}; // class PropertyResource


int main()
{
  OriginalResource ori_res{ "google.com" };
  ori_res.setPort( 8080 );
  ori_res.setPath( "/api/v1.0/status" );
  ori_res.setUser( { "john", "pwd" } );
  printLine( ori_res.getURL() );
  std::cout << ori_res.getHost() << std::endl;

  PropertyResource prp_res{ "google.com" };
  prp_res.port = 8080;
  prp_res.path = "/api/v1.0/status";
  prp_res.user = User{ "john", "pwd" };
  printLine( prp_res.URL );
  std::cout << prp_res.host() << std::endl;

  return 0;
}

// Impl

std::string toURL( const std::string& host, int port, const std::string& path,
  const std::string& user_name, const std::string& user_secret )
{
  std::stringstream ss;
  if ( !user_name.empty() )
  {
    ss << user_name;
    if ( !user_secret.empty() )
      ss << ':' << user_secret;
    ss << '@';
  }
  ss << host;
  if ( port != 0 )
    ss << ':' << port;
  if ( !path.empty() )
    ss << path;
  return ss.str();
}

void printLine( const std::string& line )
{
  std::cout << line << std::endl;
}
