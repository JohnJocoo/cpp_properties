
#error "This file is for documentational purpose only"

/* This file attempts to auto-document Properties
 * interface with something close to Concepts.
 * Note that "parent class" means class that own 
 * property as it's member.
 * [[noaddress]] attribute means that taking the
 * address of value, returned by reference is discouraged.
 */

struct Concept
{
  // Everything that inherits Concept
  // is Concept itself - not an actual class,
  // but declaration of interface
};

struct Any : Concept
{
  // Represents any type 
};

template < typename T1, typename T2 >
struct OneOf : Concept
{
  // Stub to define that actual type
  // can be either T1 or T2
};

template < typename T >
class ReadableProperty : Concept
{
public:
  using ValueOrCRef = OneOf< T, const T& >;

public:
  [[nodiscard]] ValueOrCRef operator()() const;
  [[nodiscard]] operator ValueOrCRef() const;
  ReadableProperty& operator=( Any ) = delete;

}; // class ReadableProperty

template < typename T >
class WritableProperty : Concept
{
public:
  WritableProperty& operator=( Any );

}; // class WritableProperty

template < typename T >
class RealValueReadableProperty : ReadableProperty< T >
{
public:
  [[nodiscard, noaddress]] const T& operator()() const noexcept;
  [[nodiscard, noaddress]] operator const T&() const noexcept;

protected: // Must be accessable by parent class
  [[nodiscard]] const T& cref() const noexcept;

}; // class RealValueReadableProperty

template < typename T >
class OwningReadableProperty : RealValueReadableProperty< T >
{
protected: // Must be accessable by parent class
  OwningReadableProperty& operator=( Any );
  [[nodiscard]] T& ref() noexcept;

}; // class OwningReadableProperty

template < typename T >
class ImaginaryReadableProperty : ReadableProperty< T >
{
public:
  [[nodiscard]] T operator()() const;
  [[nodiscard]] operator T() const;

}; // class ImaginaryReadableProperty
