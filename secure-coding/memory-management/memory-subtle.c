#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
  const int arraySize = 5;
  int *numbers = (int *)malloc(arraySize * sizeof(*numbers));
  // do calloc
  //int *numbers = (int *)calloc(arraySize, sizeof(*numbers));

  if(numbers ! = NULL)
  {
    memset(numbers, 0, arraySize * sizeof(*numbers));
    // Memory allocation is successful
    // Use the allocated memory for operations
    for (int i = 0; i < arraySize; i++)
    {
      numbers[i] += 2 * i; // assuming numbers[i] == 0, this is not gauranteed
      printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    // Deallocates the memory block
    free(numbers);
  }

  return 0;
}
