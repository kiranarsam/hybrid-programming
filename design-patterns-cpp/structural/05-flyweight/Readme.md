## FlyWeight
- Space optimization

## Motivation
- Avoid redundancy when storing data

- E.g., MMORPG
    - Plenty of users with identical first / last names
    - No sense in storing same first/last name over and over again
    - Store a list of names and pointers to them

- E.g., bold or italic text in the console
    - Don't want each character to have formatted character
    - Operate on ranges (e.g., line number, start/end positions)

## FlyWeight
- A space optimization technique that lets us use less memory by
  storing externally the data associated with similar objects

## Summary
- Store common data externally
    e.g., static map

- Define the idea of 'ranges' on homogeneous collections
    - Store data related to those ranges.
