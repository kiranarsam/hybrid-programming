## Observer
- Getting notification when things happen.

## Motivation
- We need to be informed when certain things happen
    - Object's field changes
    - Object does something
    - Some external event occurs

- We want to listen to events and notified when they occurs
- Terminology:
    - event and subscriber
    - signal and slot (Boost, Qt, etc)

## Observer
- An observer is an object that wishes to be informed about events
  happening in the system. The entity generating the events is
  an observable.

## Summary
- Two participants:
    - Observable provides a way of subscribing to an event (signal)
    - Observer performs the subscription

- Observable implementation is always intrusive (observer doesn't need to be)
- Multithreading / reentrant use can cause issues
- Ready-made implementation of Observer are available
