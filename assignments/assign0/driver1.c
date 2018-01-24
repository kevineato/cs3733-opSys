#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myio.h"

int main(int argc, char *argv[]) {
  /* Check for correct count of command line arguments */
  if (argc != 4) {
    fprintf(stderr, "Usage: %s nInts nDoubles nLines\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int i; /* Keeps track of how many ints, doubles, and lines */

  /* Receive and print nInts */
  int maxInt = INT_MIN; /* Track max int received */
  if ((i = atoi(argv[1])) >= 0) {
    for (int j = 0; j < i; j++) {
      int num = ReadInteger();
      printf("%d. Integer entered: %d\n", j + 1, num);

      if (num > maxInt)
        maxInt = num;
    }
  } else {
    fprintf(stderr, "Invalid number of integers\n");
    exit(EXIT_FAILURE);
  }
  printf("\n");

  /* Receive and print nDoubles */
  double maxDub = DBL_MIN; /* Track max double receieved */
  if ((i = atoi(argv[2])) >= 0) {
    for (int j = 0; j < i; j++) {
      double dub = ReadDouble();
      printf("%d. Double entered: %lf\n", j + 1, dub);

      if (dub > maxDub)
        maxDub = dub;
    }
  } else {
    fprintf(stderr, "Invalid number of doubles\n");
    exit(EXIT_FAILURE);
  }
  printf("\n");

  char *maxStr = NULL; /* Track current longest string */
  int maxLen = INT_MIN; /* Track current longest string length */
  if ((i = atoi(argv[3])) >= 0) {
    for (int j = 0; j < i; j++) {
      char *str = ReadLine();
      printf("%d. String entered: %s\n", j + 1, str);

      int len = strlen(str);
      if (len > maxLen) {
        /* Don't free if maxLen is still initial value */
        if (maxLen != INT_MIN)
          free(maxStr);

        maxStr = str;
        maxLen = len;
      } else {
        /* Free current str since not needed if shorter than maxStr */
        free(str);
      }
    }
  } else {
    fprintf(stderr, "Invalid number of lines\n");
    exit(EXIT_FAILURE);
  }

  /* Print three max values received */
  printf("\nMax integer entered: %d\n", maxInt);
  printf("Max double entered: %lf\n", maxDub);
  printf("Longest string entered: %s\n", maxStr);

  /* Free maxStr that was alloced earlier */
  free(maxStr);

  exit(EXIT_SUCCESS);
}
