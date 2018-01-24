#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "myio.h"

int main (int argc, char *argv[]) {
  /* Check for correct count of command line arguments */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *inFile = NULL;
  FILE *outFile = NULL;

  /* Open input_file for reading, exit if error */
  inFile = fopen(argv[1], "r");
  if (inFile == NULL) {
    perror("Error opening input file");
    exit(EXIT_FAILURE);
  }

  /* Open output_for writing, exit if error */
  outFile = fopen(argv[2], "w");
  if (outFile == NULL) {
    perror("Error opening output file");
    exit(EXIT_FAILURE);
  }

  char c;
  int foundSpace = 0; /* 1 if c is a space, 0 otherwise */

  while ((c = fgetc(inFile)) != EOF) {
    /* Check if c is space, which is 0x20 in ASCII hex */
    if ((int) c != 0x20) {
      foundSpace = 0; /* Did not find space */
      fputc(c, outFile); /* Output non-space character to outFile */
    } else if (!foundSpace) {
      foundSpace = 1; /* Previous character wasn't a space, set to 1 */
      fputc(c, outFile); /* Output single space, loop will skip until non-space */
    }
  }

  /* Close both previously opened files */
  fclose(inFile);
  fclose(outFile);

  exit(EXIT_SUCCESS);
}
