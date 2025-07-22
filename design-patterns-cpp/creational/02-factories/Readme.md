## Motivation
- Object creation logic becomes too convoluted.

- Constructor is not descriptive
    * Name mandated by name of containing type
    * Cannot overload with same sets of arguments with different names
    * can turn into 'optional parameter hell'

- Object creation (non-piecewise, unlike Builder) can be outsourced to
    * A separate function (Factory Method)
    * That may exist in a separate class (Factory)
    * Can create hierarchy of factories with Abstract Factory

## Factory Design pattern
* A component responsible soley for the wholesale (not-piecewise) creation of
  objects.

## Summary:
* A factory method is a static method that creates objects.

* A factory can take care of object creation

* A factory can be external or reside inside the object as an inner class

* Hierarchies of factories can be used to create related objects.
