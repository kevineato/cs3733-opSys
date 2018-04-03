#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "pagetable.h"
#include "phypages.h"

#define OPEN_PERMS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
/* Part 2 page, virtual memory, and physical memory size in bytes */
#define PAGE_SIZE 128
#define VMEM_SIZE 4096
#define PMEM_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s ADDR_SEQ_FILE\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int fdIn;
  if ((fdIn = open(argv[1], O_RDONLY)) == -1) {
    fprintf(stderr, "Error opening %s: ", argv[1]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  int fdOut;
  char *outName;
  if (strstr(argv[1], "test"))
    outName = "output-part2test";
  else
    outName = "output-part2";

  if ((fdOut = open(outName, O_WRONLY | O_CREAT | O_TRUNC, OPEN_PERMS)) == -1) {
    fprintf(stderr, "Error opening %s: ", outName);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  /* Allocate page table and frame table given respective sizes */
  pageTab *pTab = initPageTab(PAGE_SIZE, VMEM_SIZE);
  frameTab *fTab = initFrameTab(PAGE_SIZE, PMEM_SIZE);

  int numRead;
  int numWrite;
  int numFaults = 0; // Keep track of number of page faults
  int pshiftBits = (int) log2(PAGE_SIZE); // Num bits for page index
  int oBits = PAGE_SIZE - 1; // Max value for bits in page size for offset
  unsigned long addr;
  while ((numRead = read(fdIn, &addr, 8))) {
    if (numRead == 8) {
      unsigned long page = addr >> pshiftBits;
      unsigned long offset = addr & oBits;
      /* Get frame number from page table */
      /* Also increments numFaults if there was a page fault */
      int frame = getFrame(pTab, fTab, page, &numFaults);
      unsigned long physical = frame * PAGE_SIZE + offset;
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

  close(fdIn);
  close(fdOut);
  /* Free page and frame tables */
  delPageTab(pTab);
  delFrameTab(fTab);

  /* Print number of page faults */
  printf("Number of page faults: %d\n", numFaults);

  return 0;
}
