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

  /* add to total 'R' and count 'r' in s1 */
  for (int i = 0; i < len1; i++) {
    if (s1[i] == 'R')
      totalR++;

    if (s1[i] == 'r')
      countr1++;
  }

  /* add to total 'R' and count 'r' in s2 */
  for (int i = 0; i < len2; i++) {
    if (s2[i] == 'R')
      totalR++;

    if (s2[i] == 'r')
      countr2++;
  }

  /* calculate average of count 'r' */
  double avgwait = (countr1 + countr2) / 2.0;
  /* calculate ratio of total 'R' to longest length */
  double ratioR = (double)totalR / maxlen;

  printf("%d %d %.1lf %.5lf\n", countr1, countr2, avgwait, ratioR);
}

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int total = x1 + y1 + z1 + x2 + y2 + z2;

  /* set all to 0 for pre-emptive null terminators */
  memset(s1, 0, total);
  memset(s2, 0, total);

  /* keep track of current position letters are being inserted into s1 and s2 */
  int curr1 = 0;
  int curr2 = 0;

  /* output x1 for both */
  while (x1 > 0) {
    s1[curr1++] = 'R';
    s2[curr2++] = 'r';
    x1--;
  }

  /* p1 waits */
  if (y1 > 0) {
    while (y1 > 0) {
      s1[curr1++] = 'w';
      y1--;
    }

    /* p2 runs while p1 waits */
    while (x2 > 0) {
      s2[curr2++] = 'R';
      x2--;
    }

    /* if p1 current position < p2 pad with 'r' */
    while (curr1 < curr2)
      s1[curr1++] = 'r';

    /* p2 waits */
    if (y2 > 0) {
      while (y2 > 0) {
        s2[curr2++] = 'w';
        y2--;
      }

      /* p1 finishes while p2 waits */
      while (z1 > 0) {
        s1[curr1++] = 'R';
        z1--;
      }

      /* if p2 current position < p1 pad with 'r' */
      while (curr2 < curr1)
        s2[curr2++] = 'r';

      /* p2 finishes */
      while (z2 > 0) {
        s2[curr2++] = 'R';
        z2--;
      }
      /* p2 doesn't wait */
    } else {
      /* p1 ready while p2 finishes */
      while (z2 > 0) {
        s2[curr2++] = 'R';
        s1[curr1++] = 'r';
        z2--;
      }

      /* p1 finishes */
      while (z1 > 0) {
        s1[curr1++] = 'R';
        z1--;
      }
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

