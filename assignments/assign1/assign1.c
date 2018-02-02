#include <stdio.h>
#include <stdlib.h>

#include "pslibrary.h"

int main(int argc, char *argv[]) {
  /* check for correct num command line args */
  if (argc != 8) {
    fprintf(stderr, "Must pass 7 integer args to %s\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* header for program */
  printf("Assignment 1 program was written by Kevin Wilson\n");
  printf("inputs: ");
  for (int i = 1; i < argc; i++) {
    printf("%s ", argv[i]);
  }
  printf("\n");

  /* convert args to integers and add up last 6 */
  int x1 = atoi(argv[2]);
  int y1 = atoi(argv[3]);
  int z1 = atoi(argv[4]);
  int x2 = atoi(argv[5]);
  int y2 = atoi(argv[6]);
  int z2 = atoi(argv[7]);
  int total = x1 + y1 + z1 + x2 + y2 + z2;

  char *heading = "Part 1\n";
  /* allocate total of last 6 args for s1 and s2 */
  char *s1 = (char *)malloc(total);
  char *s2 = (char *)malloc(total);

  fcfsa(s1, s2, x1, y1, z1, x2, y2, z2);
  display(heading, s1, s2);

  /* free allocated s1 and s2 */
  free(s1);
  free(s2);

  return 0;
}
