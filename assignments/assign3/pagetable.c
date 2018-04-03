#include <stdlib.h>

#include "pagetable.h"
#include "phypages.h"

pageTab *initPageTab(int pageSize, int vmemSize) {
  /* Allocate page table structure */
  pageTab * pTab = (pageTab *) malloc(sizeof(pageTab));

  int nPages = vmemSize / pageSize;
  /* Allocate array of page table entries (ptes) */
  pte *ptes = (pte *) malloc(sizeof(pte) * nPages);

  /* Set all ptes to frame 0 and invalid */
  for (int i = 0; i < nPages; i++) {
    ptes[i].frame = 0;
    ptes[i].valid = 0;
  }

  pTab->ptes = ptes;
  pTab->pageSize = pageSize;
  pTab->nPages = nPages;
  return pTab;
}

int getFrame(pageTab *pTab, frameTab *fTab, int page, int *numFaults) {
  /* If page is valid, update LRU list since this is most recently used */
  /* and return the current frame in page table */
  if (pTab->ptes[page].valid) {
    updateLru(fTab, pTab->ptes[page].frame);
    return pTab->ptes[page].frame;
  }

  /* Must assign a frame to this invalid pte */
  int invalid = assignFrame(pTab, fTab, page);
  /* Increment page faults */
  *numFaults += 1;
  /* If assignFrame returned an invalidated pte, make it invalid */
  if (invalid != -1)
    pTab->ptes[invalid].valid = 0;

  /* Return newly assigned frame for pte */
  return pTab->ptes[page].frame;
}

/* Free page table structure */
void delPageTab(pageTab *pTab) {
  free(pTab->ptes);
  free(pTab);
}
