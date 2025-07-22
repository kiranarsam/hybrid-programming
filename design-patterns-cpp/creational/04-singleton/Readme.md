## Singleton
- A design pattern everyone loves to hate... but is it really that bad?

## Motivation
* For some components it only makes sense to have one in the system
    - Database repository
    - Object Factory

* E.g., the constructor call is expensive
    - We only do it one
    - We provide everyone with the same instance

* Want to prevent anyone creating additional copies

* Need to take care of lazy instantiation and thread safety

## Singleton
* --> A component which is instantiated only once.

## Summary
- Making a 'safe' Singleton is easy
    - Hide or delete the type's constructor, copy constructor and copy assignment operators.
    - Create a static method that returns a reference to a static member
    - Gaurenteed to be thread-safe since C++11

- Types with 'hard' dependencies on singletons are difficult to test
    - Cannot decouple the singleton and supply a fake object

- Instead of directly using a singleton, consider depending on an abstraction (e.g, an Interface)

- Consider defining singleton lifetime in DI (Dependency Injection) contatiner.
