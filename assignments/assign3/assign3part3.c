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

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "Usage: %s PAGE_SIZE VMEM_SIZE PHYMEM_SIZE ADDR_SEQ_FILE\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Get arguments for page, virtual memory, and physical memory sizes in bytes */
  int pageSize = atoi(argv[1]);
  int vmemSize = atoi(argv[2]);
  int pmemSize = atoi(argv[3]);

  int fdIn;
  if ((fdIn = open(argv[4], O_RDONLY)) == -1) {
    fprintf(stderr, "Error opening %s: ", argv[4]);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  int fdOut;
  char *outName;
  if (strstr(argv[4], "test"))
    outName = "output-part3test";
  else
    outName = "output-part3";

  if ((fdOut = open(outName, O_WRONLY | O_CREAT | O_TRUNC, OPEN_PERMS)) == -1) {
    fprintf(stderr, "Error opening %s: ", outName);
    perror(NULL);
    exit(EXIT_FAILURE);
  }

  pageTab *pTab = initPageTab(pageSize, vmemSize);
  frameTab *fTab = initFrameTab(pageSize, pmemSize);

  int numRead;
  int numWrite;
  int numFaults = 0;
  unsigned long addr;
  int pshiftBits = (int) log2(pageSize);
  int oBits = pageSize - 1;
  while ((numRead = read(fdIn, &addr, 8))) {
    if (numRead == 8) {
      unsigned long page = addr >> pshiftBits;
      unsigned long offset = addr & oBits;
      int frame = getFrame(pTab, fTab, page, &numFaults);
      unsigned long physical = frame * pageSize + offset;
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
  delPageTab(pTab);
  delFrameTab(fTab);

  printf("Number of page faults: %d\n", numFaults);

  return 0;
}
