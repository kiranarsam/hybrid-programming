## Strategy
- System behavior partially specified at runtime.

## Motivation
- Many algorithms can be decomposed into higher- and lower- level parts.
- Making tea can be decomposed into
    - The process of making of hot beverage (boil water, pour into cup); and
    - Tea-sepecific things (put teabag into water)
- The high-level alogorithm can then be reused for making coffee or hot chocolate
    - Supported by beverage-specific strategies

## Strategy
- Enables the exact behavior of a system to be selected either at run-time (dynamic) or compile-time (static).
- Also known as a policy (esp. in the C++ world.)

## Summary
- Define a algorithm at a high level
- Define the interface you expect each strategy to follow
- Provide for either dynamic or static composition of strategy in the overall algorithm.
