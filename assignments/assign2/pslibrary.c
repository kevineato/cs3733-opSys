#include <stdio.h>
#include <string.h>

#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

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

  printf("%d %d %.1lf %.5lf\n\n", countr1, countr2, avgwait, ratioR);
}

void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                   /* next string position (time) */
  int state1 = READY;                            /* start with both ready */
  int state2 = READY;
  int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
  int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
  int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
  int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

  for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                            /* running process completes its CPU burst */
    if ((state1 == RUNNING) && (cpuLeft1== 0)) {
      if (ioLeft1 == 0) {
        state1 = DONE;
        s1[i] = stateChars[state1];            /* terminate the string */
      }
      else
        state1 = WAITING;
    }
    else if ((state2 == RUNNING) && (cpuLeft2 == 0)) {
      if (ioLeft2 == 0) {
        state2 = DONE;
        s2[i] = stateChars[state2];
      }
      else
        state2 = WAITING;
    }
                                                   /* handle IO complete */
    if ((state1 == WAITING) && (ioLeft1 == 0)) {
      state1 = READY;
      cpuLeft1 = z1;
    }
    if ((state2 == WAITING) && (ioLeft2 == 0)) {
      state2 = READY;
      cpuLeft2 = z2;
    }

    if ((state1 == READY) && (state2 == READY)) {
      state1 = RUNNING;
    }
                                   /* handle one ready and CPU available */
    else if ((state1 == READY) && (state2 != RUNNING)) {
      state1 = RUNNING;
    }
    else if ((state2 == READY) && (state1 != RUNNING)) {
      state2 = RUNNING;
    }
/* insert chars in string, but avoid putting in extra string terminators */
    if (state1 != DONE)
      s1[i] = stateChars[state1];
    if (state2 != DONE)
      s2[i] = stateChars[state2];
                                                      /* decrement counts */
    if (state1 == RUNNING)
      cpuLeft1--;
    if (state1 == WAITING)
      ioLeft1--;
    if (state2 == RUNNING)
      cpuLeft2--;
    if (state2 == WAITING)
      ioLeft2--;
  }                                               /* end of main for loop */
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                   /* next string position (time) */
  int state1 = READY;                            /* start with both ready */
  int state2 = READY;
  int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
  int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
  int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
  int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

  for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                            /* running process completes its CPU burst */
    if ((state1 == RUNNING) && (cpuLeft1== 0)) {
      if (ioLeft1 == 0) {
        state1 = DONE;
        s1[i] = stateChars[state1];            /* terminate the string */
      }
      else
        state1 = WAITING;
    }
    else if ((state2 == RUNNING) && (cpuLeft2 == 0)) {
      if (ioLeft2 == 0) {
        state2 = DONE;
        s2[i] = stateChars[state2];
      }
      else
        state2 = WAITING;
    }
                                                   /* handle IO complete */
    if ((state1 == WAITING) && (ioLeft1 == 0)) {
      state1 = READY;
      cpuLeft1 = z1;
    }
    if ((state2 == WAITING) && (ioLeft2 == 0)) {
      state2 = READY;
      cpuLeft2 = z2;
    }

    if ((state1 == READY) && (state2 == READY)) {
      if (cpuLeft2 < cpuLeft1)
        state2 = RUNNING;
      else
        state1 = RUNNING;
    }
                                   /* handle one ready and CPU available */
    else if ((state1 == READY) && (state2 != RUNNING)) {
      state1 = RUNNING;
    }
    else if ((state2 == READY) && (state1 != RUNNING)) {
      state2 = RUNNING;
    }
/* insert chars in string, but avoid putting in extra string terminators */
    if (state1 != DONE)
      s1[i] = stateChars[state1];
    if (state2 != DONE)
      s2[i] = stateChars[state2];
                                                      /* decrement counts */
    if (state1 == RUNNING)
      cpuLeft1--;
    if (state1 == WAITING)
      ioLeft1--;
    if (state2 == RUNNING)
      cpuLeft2--;
    if (state2 == WAITING)
      ioLeft2--;
  }                                               /* end of main for loop */
}

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                   /* next string position (time) */
  int state1 = READY;                            /* start with both ready */
  int state2 = READY;
  int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
  int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
  int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
  int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

  for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                            /* running process completes its CPU burst */
    if ((state1 == RUNNING) && (cpuLeft1== 0)) {
      if (ioLeft1 == 0) {
        state1 = DONE;
        s1[i] = stateChars[state1];            /* terminate the string */
      }
      else
        state1 = WAITING;
    }
    else if ((state2 == RUNNING) && (cpuLeft2 == 0)) {
      if (ioLeft2 == 0) {
        state2 = DONE;
        s2[i] = stateChars[state2];
      }
      else
        state2 = WAITING;
    }
                                                   /* handle IO complete */
    if ((state1 == WAITING) && (ioLeft1 == 0)) {
      state1 = READY;
      cpuLeft1 = z1;

      if (cpuLeft1 < cpuLeft2) {
        state1 = RUNNING;

        if (state2 == RUNNING)
          state2 = READY;
      }
    }
    if ((state2 == WAITING) && (ioLeft2 == 0)) {
      state2 = READY;
      cpuLeft2 = z2;

      if (cpuLeft2 < cpuLeft1) {
        state2 = RUNNING;

        if (state1 == RUNNING)
          state1 = READY;
      }
    }

    if ((state1 == READY) && (state2 == READY)) {
      if (cpuLeft2 < cpuLeft1)
        state2 = RUNNING;
      else
        state1 = RUNNING;
    }
                                   /* handle one ready and CPU available */
    else if ((state1 == READY) && (state2 != RUNNING)) {
      state1 = RUNNING;
    }
    else if ((state2 == READY) && (state1 != RUNNING)) {
      state2 = RUNNING;
    }
/* insert chars in string, but avoid putting in extra string terminators */
    if (state1 != DONE)
      s1[i] = stateChars[state1];
    if (state2 != DONE)
      s2[i] = stateChars[state2];
                                                      /* decrement counts */
    if (state1 == RUNNING)
      cpuLeft1--;
    if (state1 == WAITING)
      ioLeft1--;
    if (state2 == RUNNING)
      cpuLeft2--;
    if (state2 == WAITING)
      ioLeft2--;
  }                                               /* end of main for loop */
}

void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2) {
  int i;                                   /* next string position (time) */
  int state1 = READY;                            /* start with both ready */
  int state2 = READY;
  int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
  int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
  int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
  int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
  int qLeft = quantum;

  for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                            /* running process completes its CPU burst */
    if ((state1 == RUNNING) && (cpuLeft1== 0)) {
      if (ioLeft1 == 0) {
        state1 = DONE;
        s1[i] = stateChars[state1];            /* terminate the string */
      }
      else
        state1 = WAITING;
    }
    else if ((state2 == RUNNING) && (cpuLeft2 == 0)) {
      if (ioLeft2 == 0) {
        state2 = DONE;
        s2[i] = stateChars[state2];
      }
      else
        state2 = WAITING;
    }

    if ((state1 == RUNNING) && (qLeft == 0)) {
      state1 = READY;

      if (state2 == READY) {
        state2 = RUNNING;
        qLeft = quantum;
      }
    }
    if ((state2 == RUNNING) && (qLeft == 0)) {
      state2 = READY;

      if (state1 == READY) {
        state1 = RUNNING;
        qLeft = quantum;
      }
    }
                                                   /* handle IO complete */
    if ((state1 == WAITING) && (ioLeft1 == 0)) {
      state1 = READY;
      cpuLeft1 = z1;
    }
    if ((state2 == WAITING) && (ioLeft2 == 0)) {
      state2 = READY;
      cpuLeft2 = z2;
    }

    if ((state1 == READY) && (state2 == READY)) {
      state1 = RUNNING;
      qLeft = quantum;
    }
                                   /* handle one ready and CPU available */
    else if ((state1 == READY) && (state2 != RUNNING)) {
      state1 = RUNNING;
      qLeft = quantum;
    }
    else if ((state2 == READY) && (state1 != RUNNING)) {
      state2 = RUNNING;
      qLeft = quantum;
    }
/* insert chars in string, but avoid putting in extra string terminators */
    if (state1 != DONE)
      s1[i] = stateChars[state1];
    if (state2 != DONE)
      s2[i] = stateChars[state2];
                                                      /* decrement counts */
    qLeft--;
    if (state1 == RUNNING)
      cpuLeft1--;
    if (state1 == WAITING)
      ioLeft1--;
    if (state2 == RUNNING)
      cpuLeft2--;
    if (state2 == WAITING)
      ioLeft2--;
  }                                               /* end of main for loop */
}

