# memory management pitfalls
1. Memory leaks
2. Buffer overflows
3. Dangaling pointers

Memory leaks - Occurs when allocated memory is not released. Memory exhaustion
Buffer overflows - Happens when we write data beyond the boundaries of a buffer.
Dangling Pointer - A pointer left pointing to a freed memory.

## Secure Coding principles
1. Memory management
2. Bounds checking
3. Safe string functions
4. Pointer validation
5. Use of smart pointers - automatic allocate or deallocate memory

## Pointer Pitfalls
1. Null pointer dereferencing - Accessing or modifying memory pointed to by a null pointer
2. uninitialized pointers - pointer declared without being initialized
3. pointer arithmetic - resulting pointer accesses invalid memory
4. Dangling pointer - points to deallocated memory


## Pointer best practises
1. Initialize your pointers
2. Validate pointers before use
3. Pair allocations with deallocations
4. Refrain from using pointer arithmetic

## Key security principles
1. Principle of Least Privilege - only give a process the privileges needed to do its job
2. Principle of Fail-Safe Defaults - Access is denied unless explicitily granted

## Type system best practises
1. Avoid implicit conversions - the compiler automatically converts one type to another
2. Use Explicit type conversions - Types are converted using designated cast operators
3. Be mindful of type sizes - The size of types in C/C++ can vary across platforms and architectures.
4. validate input - validate and sanitize user input and external data.

## C++ Casting oeprators
1. const_cast
2. dynamic_cast
3. reinterpret_cast
4. static_cast
