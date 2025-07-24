## Template Method
- A high-level blueprint for an algorithm to be completed by inheritors.

## Motivation
- Algorithms can be decomposed into common parts + specifics

- Strategy pattern does this through composition
    - High-level algorithm uses an interface
    - Concrete implementations implement the interface

- Template Method does the same thing through inheritance
    - Overall algorithm makes use of abstract member
    - Inheritors override the abstract members
    - Parent template method invoked

## Template Method
- Allows us to define the 'skeleton' of the algorithm, with concrete implementations defined in subclasses.

## Summary
- Define an algorithm at a high-level

- Define constituent parts as abstract methods

- Inherit the algorithm class, providing necessary overrides
