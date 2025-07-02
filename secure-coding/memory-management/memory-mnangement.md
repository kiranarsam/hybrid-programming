# Memory Management in C
1. malloc()
   Allocates a block of memory of a specified size
   Returns a pointer to the allocated memory block
   free() deallocates previously allocated memory

2. calloc()
   Allocates a block of memory of a specified size
   Returns a pointer to the allocated memory block
   Initializes allocated memory to zero
   free() deallocates previously allocated memory

3. realloc()
   Resizes an existing memory block
   Takes a pointer and the new size in bytes

4. aligned_alloc()
   Allocates memory with a specific alignment.
   Arranges data in memory for efficient access
   Aligned Memory - The starting address is a multiple of a power of two number.

# Memory Management Errors
## Dereferencing null pointers
Null Pointer - Does not point to a valid memory address.
* Usally crashes the app
* May lead to uncontrolled code execution

```C
int *ptr = NULL;
*ptr = 20; // dereferencing null pointers
```

How to avoid: Check if the pointer to null
```C
if(ptr != NULL)
{
  *ptr = 20;
}
```

## Referencing freed memory
- can easily go unnoticed
- Leads to undefined behavior and data corruption

```C
int *value = (int *)malloc(sizeof(int));
free(value);

// ... DO some operations

// forgot that value was freed and try to use it
*value = 46; // value points to freed memory

```

How to avoid:
```C
int *value = (int *)malloc(sizeof(int));
free(value);
value = NULL; // set to NULL after calling free

// ... DO some operations

// forgot that value was freed and try to use it
*value = 46; // this will cause runtime error

```

## Freeing the same memory multipled times
- Freed memory becomes available for reuse
- Freeing the same memory block again leads to undefined behavior
```C
int *array = (int *)malloc(5 * sizeof(int));
free(array);

// Do some operations

// forgot that array was freed and deallocate it again
free(array); // triggers runtime error
```

To avoid the problem, set to pointer to NULL

```C
int *array = (int *)malloc(5 * sizeof(int));
free(array);
array = NULL;

// Do some operations

// forgot that array was freed and deallocate it again
free(array); // array is NULL, and free(NULL) is a no-op
```

## Leaking memory
- unreleased memory cannot be reclaimed
- May lead to resource exhaustion
- Can be exploited to deplete the available memory

## subtle memory managment errors
- Assuming allocated memory is set to zero
- Expecting memory allocations to always succeed
    - May cause undefined


# C++ Memmory Management
* new
* delete

## new
- Allocates memory for objects
- Initializes the objects
- Returns a pointer to the allocated memory

## std::set_new_handler function
- Sets handler for memory allocation issues
- Allows implementing custom error messages

# Smart Pointers
- Object acting as pointer
- Manages its memory automatically
- No manual deallocation
- Safer and more efficient memory handling

* Unique
* Shared
* Weak

## unique_ptr
- A smart pointer that represents ownership of the dynamically allocated object.

## shared_ptr
- A smart pointer that allows shared ownership of the same dynamically allocated object.

## weak_ptr
- A smart pointer that can observe but does not own the dynamically allocated object.

circular reference:
sPtr1 = sPtr2 ==> +1
sPtr2 = sPtr ==> +1 (again plus one count)

To avoid above:
wPtr1 = sPtr1   ==> +0 ( no increase in ref count)
So, we can avoid circular reference of the shared pointer

## Benefits of smart pointers
- Automatic deallocation of memory
- Clear ownership semantics (unique, shared)
- self-documenting code
- exception safety
