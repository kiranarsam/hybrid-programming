#include <stdio.h>
#include <stdlib.h>

// There is memory leak in below code.

int main()
{
  int n = 10;

  char *buffer;

  for(int i = 0; i < n; i++) {
    buffer = (char *)malloc(100 * sizeof(*buffer));
    sprintf(buffer, "Iteration %d\n", i);
    printf("%s\n", buffer);
    // Free should be called here, to fix the memory leak
  }

  free(buffer); // free should not be called here.

  return 0;
}