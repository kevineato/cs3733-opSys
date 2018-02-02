#include <stdio.h>
#include <string.h>

void part0(char *s1, char *s2) {
  const char *strs1 = "RRwwwwwRRRRRRRRR";
  const char *strs2 = "rrRRRRwwwwwwwwrrRRRRRRR";

  strncpy(s1, strs1, strlen(strs1) + 1);
  strncpy(s2, strs2, strlen(strs2) + 1);
}

void display(char *heading, char *s1, char *s2) {
  printf("\n");
  printf("%s", heading);
  printf("%s\n", s1);
  printf("%s\n", s2);

  int len1 = strlen(s1);
  int len2 = strlen(s2);
  int maxlen = len1 > len2 ? len1 : len2;
  int countr1 = 0;
  int countr2 = 0;
  int totalR = 0;

  for (int i = 0; i < len1; i++) {
    if (s1[i] == 'R')
      totalR++;

    if (s1[i] == 'r')
      countr1++;
  }

  for (int i = 0; i < len2; i++) {
    if (s2[i] == 'R')
      totalR++;

    if (s2[i] == 'r')
      countr2++;
  }

  double avgwait = (countr1 + countr2) / 2.0;
  double avgR = (double)totalR / maxlen;

  printf("%d %d %.1lf %.5lf\n", countr1, countr2, avgwait, avgR);
}

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int total = x1 + y1 + z1 + x2 + y2 + z2;
  memset(s1, 0, total);
  memset(s2, 0, total);

  int curr1 = 0;
  int curr2 = 0;

  while (x1 > 0) {
    s1[curr1++] = 'R';
    s2[curr2++] = 'r';
    x1--;
  }

  if (y1 > 0) {
    while (y1 > 0) {
      s1[curr1++] = 'w';
      y1--;
    }

    while (x2 > 0) {
      s2[curr2++] = 'R';
      x2--;
    }
    /* p1 doesn't wait */
  } else {
    /* p2 ready while p1 finishes */
    while (z1 > 0) {
      s1[curr1++] = 'R';
      s2[curr2++] = 'r';
      z1--;
    }

    /* p2 runs to completion since p1 done */
    while (x2 > 0) {
      s2[curr2++] = 'R';
      x2--;
    }

    while (y2 > 0) {
      s2[curr2++] = 'w';
      y2--;
    }

    while (z2 > 0) {
      s2[curr2++] = 'R';
      z2--;
    }
  }
}

