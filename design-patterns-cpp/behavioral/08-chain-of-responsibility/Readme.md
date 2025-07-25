## Chain Of Responsibility:
- Sequence of handlers processing an event one after another.

## Motivation
- Unethical behavior by an employee; who takes the blame?
    - Employee
    - Manager
    - CEO

- You click a graphical element on a form
    - Button handles it, stops further processing
    - Underlying group box
    - Underlying window

- CCG computer game
    - Creature has attack and defense values
    - Those can be boosted by other cards

## Chain Of Responsibility
- A chain of responsibility who all get a chance to process a command or a query,
  optionally having default processing implementation and an ability to terminate
  the processing chain.

## Summary
- Chain of Responsibility can be implemented as
    - A chain of pointers/references (singly linked list)
    - Centralized list

- Enlist objects in the chain, possibly controlling their order

- Object removal from chain (e.g., disconnect from a signal)
