# Overview
This is a brand new C++ properties header-only library that target is to enforce encapsulation and unified get/set interface for your data classes.

The project is WIP. But even now following features are implemented:
1. Different types of properties:
    * OwningProperty - one that owns its value
    * MemberProperty - one that references class member
    * MemberFunctionProperty - one that references class member functions (getter/setter)
    * AliasProperty - property that references other property and acts as name alias
2. Unified public interface between property types. It is declared in file concepts.h. Interface is native for C++, using assignment operator as setter and conversion operator + operator() as getter.
3. Real strict encapsilation of values. No returning non-const references or pointers.
4. No initialization in constructor of class that own property is needed. Property knows everything it needs from declaration.
5. Relatively small memory overhead (1 byte for all properties, except OwningProperty with no overhead for now).
6. No double-copying in default assignment operator of class that own property.
7. Perfect forwarding in assignment operator.

You can see example of properties use in file main.cpp.


