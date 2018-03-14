# Overview
This is a brand new C++ properties header-only library that target is to enforce encapsulation and unified get/set interface for your data classes.

The project is WIP. But even now following features are implemented:
1. Different types of properties:
    * HoldingProperty - one that owns its value
    * MethodProperty - one that references class member functions (getter/setter)
2. Unified public interface between property types. It is declared in file interface.hpp. Interface is native for C++, using assignment operator as setter and conversion operator + operator() as getter.
3. Real strict encapsilation of values. No returning non-const references or pointers.
4. No initialization in constructor of class that own property is needed. Property knows everything it needs from declaration.
5. Relatively small memory overhead (1 byte for all properties, except HoldingProperty with no overhead for now).
6. No double-copying in default assignment operator of class that own property (default copy assignment operator forbidden).
7. Perfect forwarding in assignment operator.
8. More properties are to be added:
    * MemberProperty - one that references class member
    * AliasProperty - property that references other property and acts as name alias

# Example
There is an example in /example folder, here its short version.

Suppose you have a network resource class (like URL) that initialize host name in constructor, allow to get/set port, path and user info. Host name and full URL (as string) are read-only. Moreover you want to store user as separate name and secret (string), but provide public interface that get/set user as structure User. Here how this could be done using properties library:

    class Resource : prop::EnableProperties
    {
    public:
      Resource() = default;
      Resource( const std::string& host )
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
      PROP_ENABLE_PROPERTIES( Resource )
      PROP_HOLDING_PROPERTY( std::string, host, prop::ReadOnly )
      PROP_HOLDING_PROPERTY( int, port, prop::ReadWrite )
      PROP_HOLDING_PROPERTY( std::string, path, prop::ReadWrite )
      PROP_METHOD_PROPERTY( User, user, getUser, setUser, prop::ReadWrite )
      PROP_METHOD_PROPERTY( std::string, URL, getURL, prop::ReadOnly )

    }; // class Resource
    
And usage in code might look like this:

    Resource res{ "google.com" };
    res.port = 8080;
    res.path = "/api/v1.0/status";
    res.user = User{ "john", "pwd" };
    printLine( res.URL );  // void printLine(const std::string&);
    std::cout << res.host() << std::endl;
