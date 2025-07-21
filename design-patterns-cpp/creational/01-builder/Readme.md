# Builder
- When construction gets a little bit too complicated

## Motivation
- Some objects are simple and can be created in a single constructor call.
- Other objects require a lot of ceremony to create.
- Having an object with 10 constructor arguments is not productive
- Instead, opt for piecewise construction
- Builder provides an API for constructing an object step-by-step

## Builder
- When piecewise object construction is complicated, provide an API for
  doing its succintly.


## Summary
A builder is a separate component for building an object.

Can either give builder a constructor or return it via a static function.

To make builder fluent, return this.

Different facets of an object can be built with different builders working in
tandem via a base class.
