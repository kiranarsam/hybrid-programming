## Composite
Treating individual and aggregate objects uniformly

## Motivation
- Objects use other objects' fields / properties / members through inheritance and composition

- Composition lets us make compound objects
    E.g., a mathematical expression is composed of simple expressions; or
    A grouping of shapes that consists of several shapes.

- This pattern is used to treat both single (scalar) and composite objects uniformly
    .i.e., Foo and collection <Foo> have common APIs

## Composite Design Pattern
* A mechanism for treating individual (scalar) objects and compositions of
    objects in a uniform manner.

## Summary
- Objects can use other objects via inheritance/composition
- Some composed and sigular objects need similar/identical behaviours
- Composite design pattern lets us treat both types of objects uniformly
- C++ uses "duck typing", expecting enumerable types to provide begin()/end()
- A single object  can masquerade as a collection
    . Foo *begin() { return this; }
    . Foo *end() { return this + 1;}
