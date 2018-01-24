#include <stdio.h>
#include <stdlib.h>

#include "myio.h"

int ReadInteger() {
  while (1) {
    printf("Enter an integer: ");
    /* Receive input as string to scan later */
    char line[255];
    scanf("%254s", line);

    char c;
    int num;
    /* If count returned != 1, entered something other than integer */
    if (sscanf(line, "%d%c", &num, &c) == 1)
      return num;
    else
      fprintf(stderr, "Only integers are allowed. Try again.\n");
  }
}

double ReadDouble() {
  while (1) {
    printf("Enter a double: ");
    /* Receive input as string to scan later */
    char line[255];
    scanf("%254s", line);

    char c;
    double dub;
    /* If count returned != 1, entered something other than double */
    if (sscanf(line, "%lf%c", &dub, &c) == 1)
      return dub;
    else
      fprintf(stderr, "Only doubles are allowed. Try again.\n");
  }
}

char *ReadLine() {
  printf("Enter a string: ");
  return ReadLineFile(stdin);
}

char *ReadLineFile(FILE *infile) {
  char c;
  int cap = 2; /* Limit to number of chars in buffer */
  int size = 0; /* Actual number of chars in buffer */
  char *strBuff = (char *) malloc(sizeof(char) * cap);

  /* If first char '\n' discard, else add to buffer */
  if ((c = fgetc(infile)) != '\n')
    strBuff[size++] = c;

  /* Loop through infile adding each char until '\n' or EOF */
  while ((c = fgetc(infile)) != '\n' && c != EOF) {
    strBuff[size++] = c;

    /* If size reaches cap, realloc doubling cap */
    if (size == cap) {
      cap *= 2;
      strBuff = (char *) realloc(strBuff, cap);
    }
  }

  /* Resize to size + 1, add '\0' terminator */
  strBuff = (char *) realloc(strBuff, size + 1);
  strBuff[size] = '\0';

  return strBuff;
}
