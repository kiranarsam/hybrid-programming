## Proxy
- An interface for accessing a particular resource.

## Motivation
- You are calling foo.bar

- This assumes that foo is in the same process as bar()

- What if, later on, you want to put all Foo-realted operations into a separate process
    - Can you avoid changing your code?

- Proxy to the rescue!
    - Same interface, entirely different behaviour

- This is called a communication proxy
    - Other types: logging, virtual, guarding, ...


## Proxy
- A class that functions as an interface to a particular resource. That
  resource may be remote, expensive to contruct, or may require logging
  or some other added functionality.

## Proxy Vs. Decorator
- Proxy provides an identical interface;
  Decorator provides an enhanced interface.

- Decorator typically aggregates (or has reference to) what it is decorating;
  Proxy doesn't have to

- Proxy might not even be working with a materilised object.

## Summary
- A proxy has the same interface as the underlying object.

- To create a proxy, simply replicate the existing interface of an object.

- Add relevant functionality to the redefined member functions

- Different proxies (communication, logging, caching, etc.,) have
  completely different behaviors.
