## Interpreter
- Interpreters are all around us. Even now, in this very room.

## Motivation
- Textual input needs to be processed
    - E.g., turned into OOP structures

## Some examples
  - Programming language compilers, interpreters and IDEs
  - HTML, XML and similar
  - Numeric expressions (3 + 4/5)
  - Regular expressions

- Turning strings into OOP based structures in a complicated process.

## Interpreter
- A component that processes structured text data. Does so by turning into
  separate lexical tokens (lexing) and then interpreting sequences of
  said tokens (parsing).

## Summary
- Barring simple cases, an interpreter acts int two stages

- Lexing turns text into a set of tokens, e.g.
    . 3 * (4 + 5) --> Lit[3] Star Lparen Lit[4] Plus Lit[5] Rparen

- Parsing tokens into meaningful constructs
    . --> Multiplcation Expression [
        Integer[3],
        AdditonExpression[
            Integer[4],
            Integer[5]
        ]
    ]

- Parsed data can then be traversed


## Interpreter explanation
https://github.com/nesteruk/tlon
