#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  /* check for correct command line args */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s FULL/PATH/PROG1 FULL/PATH/PROG2\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int pipe1[2];
  int pipe2[2];
  int ch1pid, ch2pid, numread, numwrite;
  char buf[BUFSIZ] = {0};

  /* create both pipes */
  pipe(pipe1);
  pipe(pipe2);

  /* fork first program */
  ch1pid = fork();
  if (ch1pid == 0) { // child
    /* redirect stdout to write end of pipe1 for prog1 */
    dup2(pipe1[1], STDOUT_FILENO);
    close(pipe1[0]);
    close(pipe1[1]);

    /* find prog1 name at end of path */
    char *prog1Name = strrchr(argv[1], '/');
    prog1Name++;

    /* execute prog1 given its full path and name */
    execl(argv[1], prog1Name, NULL);
    fprintf(stderr, "Error executing %s\n", argv[1]);
    exit(EXIT_FAILURE);
  } else { // parent
    /* read until pipe has been written to by prog1 */
    while (numread = read(pipe1[0], buf, BUFSIZ), numread == -1 && errno == EINTR);
    if (numread <= 0) {
      perror("Error reading from pipe1");
      close(pipe1[0]);
      close(pipe1[1]);
      close(pipe2[0]);
      close(pipe2[1]);
      exit(EXIT_FAILURE);
    }

    /* scan through stdout of prog1 and print any digits to stderr */
    char *tmptr = buf;
    while (*tmptr != '\0') {
      if (isdigit(*tmptr))
        fprintf(stderr, "%c", *tmptr);

      tmptr++;
    }

    /* write stdout of prog1 to write end of pipe2 */
    numwrite = write(pipe2[1], buf, numread);
    if (numread <= 0) {
      perror("Error writing to pipe2");
      close(pipe1[0]);
      close(pipe1[1]);
      close(pipe2[0]);
      close(pipe2[1]);
      exit(EXIT_FAILURE);
    }

    /* parent closes both ends of pipe1 and write end of pipe2 */
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);
  }

  /* fork second program */
  ch2pid = fork();
  if (ch2pid == 0) { // child
    /* redirect stdin from read end of pipe2 */
    dup2(pipe2[0], STDIN_FILENO);
    close(pipe2[0]);
    close(pipe2[1]);

    /* find prog2 name at end of path */
    char *prog2Name = strrchr(argv[2], '/');
    prog2Name++;

    /* execute prog2 given its full path and name */
    execl(argv[2], prog2Name, NULL);
    fprintf(stderr, "Error executing %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  /* parent closes read end of pipe2 */
  close(pipe2[0]);
  return 0;
}
