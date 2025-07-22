## Adapter
* Getting interface you want from the interface you have.

## Motivation
Examples:
- Electrical devices have different power (interface) requirements
    - Voltage (5V, 220V)
    - Socket/Plug type (Europe, UK, USA)

- We cannot modify our gadgets to support every possible interface
    - Some support possible (e.g., 120/220V)

- Thus, we use a special device (an adapter) to give us the interface we require from the interface we have.

## Adapter
- A contruct which adapts an existing interface X to conform to the required interface Y.

## Summary
- Implementing an Adapter is easy

- Determine the API you have and the API you need

- Create a component which aggregates (has a reference to, ...) the adaptee

- Intermediate representations can pile up: use caching and other optimizations
