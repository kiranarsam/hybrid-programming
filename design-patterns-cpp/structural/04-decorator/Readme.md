## Decorator
- Adding behavior without altering the class itself

## Motivation
- Want to augment an object with additional functionality
- Do not want to rewrite or alter existing code (OCP)
- Want to keep new functionality separate (SRP)
- Need to be able to interact with existing structures
- Two options:
    - Aggregate the decorated object
    - Inherit from the decorated object

## Decorator
- Facilitates the addition of behaviors to individual objects.

## Summary
- A dynamic decorator keeps the reference to the decorated object(s)
    - ColoredShape{Square{}}

- A static decorator uses mixin inheritance
    - ColoredShape< Square >

- Both approaches allow limitless composition
    - TransparentShape< ColoredShape < Circle > >
