## Bridge
Connecting components together through abstractions.

## Motivation
- Bridge prevents a 'Cartesian product' complexity explosion
- Example:
    - Base class ThreadScheduler
    - Can be preemptive or cooperative
    - Can run on Windows or Unix
    - End up with a 2x2 scenario: WindowsPTS, UnixPTS, WindowsCTS, UnixCTS

- Bridge pattern avoids the entity explosion

- Check Before and After images

## Bridge
A mechanism that decouples an interface (hierarchy) from an implementation (hierarchy).

## Summary
- Decouple abstraction from implementation

- Both can exist as hierarchies

- A stronger form of encapsulation
