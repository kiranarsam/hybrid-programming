## Mediator
- Facilitates communication between components

## Motivation
- Components may go in and out of a system at any time
    - Chat room participants
    - Players in an MMORPG

- It makes no sense for them to have direct references to one another
    - Those references may go dead

- Solution: have then all refer to some central component that facilitates communication.

## Mediator
- A component that facilitates communication between other components
  without then necessarily being aware of each other or having direct
  (reference) access to each other.

## Summary
- Create the mediator and have each object in the system refer to it
    - E.g., in a field

- Mediator engages in bidirectional communication with its connected components

- Mediator has functions the components can call

- Components have functions the mediator can call

- Event processing (e.g., Rx) libraries make communication easier to implement
