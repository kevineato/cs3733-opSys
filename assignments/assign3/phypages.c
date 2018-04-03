#include <stdlib.h>

#include "pagetable.h"
#include "phypages.h"

// Initializes frame table allocating memory for array of frames
// and lru ordering array for next victim selection
frameTab *initFrameTab(int pageSize, int pmemSize) {
  frameTab *fTab = (frameTab *) malloc(sizeof(frameTab));
  /* Number of frames = physical memory (bytes) / pagesize (bytes) */
  int nFrames = pmemSize / pageSize;

  /* Allocate array of frames, maps from frame to page number */
  int *frames = (int *) malloc(sizeof(int) * nFrames);
  for (int i = 0; i < nFrames; i++)
    frames[i] = -1;

  /* Allocate victim choice array, maps victim priority to frame number */
  int *orderedFrames = (int *) malloc(sizeof(int) * nFrames);
  orderedFrames[0] = -1;
  for (int i = 1; i < nFrames; i++)
    orderedFrames[i] = i;

  /* Set frame table structure attributes and return */
  fTab->frames = frames;
  fTab->orderedFrames = orderedFrames;
  fTab->pageSize = pageSize;
  fTab->nFrames = nFrames;
  return fTab;
}

/* Returns index (priority) of frame from next victim array */
int lruIndex(frameTab *fTab, int frame) {
  for (int i = 1; i < fTab->nFrames; i++) {
    if (fTab->orderedFrames[i] == frame)
      return i;
  }
  return 0;
}

/* Updates next victim array, frame set to lowest priority and adjusts others */
void updateLru(frameTab *fTab, int frame) {
  /* Get frames current position */
  int lruInd = lruIndex(fTab, frame);
  /* Move all other frames in array up one index */
  for (int i = lruInd + 1; i < fTab->nFrames; i++) {
    fTab->orderedFrames[lruInd] = fTab->orderedFrames[i];
    lruInd++;
  }
  /* Put frame at end of array (lowest priority) since just accessed */
  fTab->orderedFrames[lruInd] = frame;
}

/* Assigns new frame to page given to function */
/* Returns invalidated page number if space must be made for new page else -1 */
int assignFrame(pageTab *pTab, frameTab *fTab, int page) {
  /* Search through frames for empty frame (frames[i] == -1) */
  for (int i = 1; i < fTab->nFrames; i++) {
    /* If empty frame update LRU and return -1 since no page removed from frame */
    if (fTab->frames[i] == -1) {
      fTab->frames[i] = page;
      updateLru(fTab, i);
      pTab->ptes[page].frame = i;
      pTab->ptes[page].valid = 1;
      return -1;
    }
  }

  /* Get index of frame containing LRU page (always orderedFrames[1]) */
  int victim = fTab->orderedFrames[1];
  /* Get page number of victim selected from LRU */
  int invalid = fTab->frames[victim];
  /* Replace frame with new page */
  fTab->frames[victim] = page;
  /* Update pte for new page with frame and valid */
  pTab->ptes[page].frame = victim;
  pTab->ptes[page].valid = 1;
  /* Update LRU with newly used frame */
  updateLru(fTab, victim);

  /* Return invalidated page removed from frames */
  return invalid;
}

/* Frees previously allocated frame table structure */
void delFrameTab(frameTab *fTab) {
  free(fTab->frames);
  free(fTab->orderedFrames);
  free(fTab);
}
