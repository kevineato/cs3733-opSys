#ifndef PHYPAGES_H_
#define PHYPAGES_H_

#include "memcommon.h"

frameTab *initFrameTab(int pageSize, int pmemSize);
int lruIndex(frameTab *fTab, int frame);
void updateLru(frameTab *fTab, int frame);
void delFrameTab(frameTab *fTab);

#endif // PHYPAGES_H_
