#ifndef PSLIBRARY_H_
#define PSLIBRARY_H_

void display(char *heading, char *s1, char *s2);
void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2);
void rr(char *s1, char *s2, int quantum, int x1, int y1, int z1, int x2, int y2, int z2);

#endif // PSLIBRARY_H_
