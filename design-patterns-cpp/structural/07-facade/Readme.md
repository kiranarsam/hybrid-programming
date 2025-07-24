## Facade
- Exposing several components through a single inherface.

## Motivation
- Balancing complexity and presentation/usability

- Typical home
    - Many subsystems (electrical, plumbing, sanitation, etc.,)
    - Complex internal structure (e.g., floor layers)
    - End user is not exposed to internals

- Same with software!
    - Many systems working to provide flexibility, but ...
    - API consumers want it to 'just work'

## Facade
- Provides a simple, easy to understand/user interface over a large
  and sophisticated body of code.

## Summary
- Build a Facade to provide a simplified API over a set of classes.

- May wish to (optionally) expose internals through the facade.

- May allow users to 'escalate' to use more complex API's if they need to.
