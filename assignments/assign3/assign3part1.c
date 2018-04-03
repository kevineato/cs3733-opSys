#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPEN_PERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define PAGE_SIZE 128

const int PAGE_TABLE[] = {2, 4, 1, 7, 3, 5, 6};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s ADDR_SEQ_FILE\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Open input file with address sequences */
  int fdIn;
  if ((fdIn = open(argv[1], O_RDONLY)) == -1) {
    fprintf(stderr, "Error opening %s: ", argv[1]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  int fdOut;
  char *outName;
  if (strstr(argv[1], "test"))
    outName = "output-part1test";
  else
    outName = "output-part1";

  /* Open output file to output translated addresses */
  if ((fdOut = open(outName, O_WRONLY | O_CREAT | O_TRUNC, OPEN_PERMS)) == -1) {
    fprintf(stderr, "Error opening %s: ", outName);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  int numRead;
  int numWrite;
  unsigned long addr;
  /* Read in 8 bytes at a time */
  while ((numRead = read(fdIn, &addr, 8))) {
    if (numRead == 8) {
      /* PAGE_SIZE_BITS = log_2(PAGE_SIZE) */
      /* Page is remaining bits after rightshifting addr PAGE_SIZE_BITS = 7 */
      unsigned long page = addr >> 7;
      /* Offset is addr & 2^(PAGE_SIZE_BITS) - 1 = PAGE_SIZE - 1 = 127 */
      unsigned long offset = addr & 127;
      /* Translated is frame_num * PAGE_SIZE + offset */
      unsigned long physical = PAGE_TABLE[page] * PAGE_SIZE + offset;
      /* Write translated to output file */
      if ((numWrite = write(fdOut, &physical, 8)) == -1) {
        perror("Error writing output");
        exit(EXIT_FAILURE);
      }
    } else if (numRead == -1) {
      if (errno != EINTR) {
        fprintf(stderr, "Error reading %s: ", argv[1]);
        perror(NULL);
        exit(EXIT_FAILURE);
      }
    }
  }

  /* Close open files */
  close(fdIn);
  close(fdOut);

  return 0;
}
