#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void AllocateDeallocateMalloc()
{
  int *numbers = (int *)malloc(5 * sizeof(*numbers));

  if(numbers ! = NULL)
  {
    // Memory allocation is successful
    // Use the allocated memory for operations
    // ...
    // Deallocates the memory block
    free(numbers);
  }
}

void AllocateDeallocateCalloc()
{
  // Allocating and initializing memory for a character buffer using calloc
  char *buffer = (char *)calloc(100, sizeof(*buffer));

  if(buffer ! = NULL)
  {
    // Memory allocation is successful
    // Use the allocated memory for operations
    // ...
    // Deallocates the memory block
    free(buffer);
  }
}

void AllocateDeallocateRealloc()
{
  int *data = (int *)malloc(5 * sizeof(*data));

  if(data ! = NULL)
  {
    // Memory allocation is successful
    // Use the allocated memory for operations
    // ...

    int *temp = (int *)realloc(data, 10 * sizeof(*data));
    if(temp == NULL)
    {
      // Memory allocation is failed
      printf("realloc() failed with error = %d\n", errno);
      free(data);
    }
    else
    {
      // Memory reallocation is successful
      data = temp; // Assign the new memory to data
      // Use the resized allocated memory for operations
      // ...

      // Deallocates the memory block
      free(data);
    }
  }
}

int MemoryAlignedAlloc()
{
  // Allocating an 8-byte aligned memory block of 64 bytes
  void *hardwareBuffer = aligned_alloc(8, 64);
  if(hardwareBuffer != NULL)
  {
    // Memory allocation successful
    printf("8-byte aligned addr: %p (%ld decimal )\n", hardwareBuffer, (long)hardwareBuffer);
    // Use the aligned memory for operations
    // ...


    // Deallocates the memory block
    free(hardwareBuffer);
  }
  else
  {
    // Memory allocation failed
    printf("aligned_alloc failed with error = %d\n", errno);
    return -1;
  }

  return 0;
}

// 6-Byte aligned is not possible, only pow(n, 2) = 2, 4, 8, 16, 32, etc...
int MemoryAlignedAllocInvalidArgument()
{
  // Allocating an 8-byte aligned memory block of 64 bytes
  void *hardwareBuffer = aligned_alloc(6, 64);
  if(hardwareBuffer != NULL)
  {
    // Memory allocation successful
    printf("6-byte aligned addr: %p (%ld decimal )\n", hardwareBuffer, (long)hardwareBuffer);
    // Use the aligned memory for operations
    // ...


    // Deallocates the memory block
    free(hardwareBuffer);
  }
  else
  {
    // Memory allocation failed
    printf("aligned_alloc failed with error = %d\n", errno);
    return -1;
  }

  return 0;
}




int main()
{
  AllocateDeallocateMalloc();
  AllocateDeallocateCalloc();
  return 0;
}