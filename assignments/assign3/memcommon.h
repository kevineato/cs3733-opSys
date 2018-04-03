#ifndef MEMCOMMON_H_
#define MEMCOMMON_H_

// Header for common functions/structs for memory management implementation

typedef struct frameTab {
  int pageSize;
  int nFrames;
  int *frames; // maps from frame to page nums
  int *orderedFrames; // maps from lru priority to frame num
} frameTab;

typedef struct pte {
  int frame;
  unsigned int valid: 1;
} pte;

typedef struct pageTab {
  int pageSize;
  int nPages;
  pte *ptes;
} pageTab;

int assignFrame(pageTab *pTab, frameTab *fTab, int page);
int getFrame(pageTab *pTab, frameTab *fTab, int page, int *numFaults);

#endif // MEMCOMMON_H_
