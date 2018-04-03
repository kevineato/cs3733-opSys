#ifndef PAGETABLE_H_
#define PAGETABLE_H_

#include "memcommon.h"

pageTab *initPageTab(int pageSize, int vmemSize);
void delPageTab(pageTab *pTab);

#endif // PAGETABLE_H_
