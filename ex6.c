/* 
 * Copyright (C) Armand Mousavi
 * Email: amousavi@uw.edu
 *
 * Starter code from lecture 4/13/2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Copy a file one character at a time in reverse
 * order to stdout. File specified as only argument */
int main(int argc, char **argv) {
  FILE *f;
  int64_t lSize;
  // Take the filename from command line arguments
  if (argc != 2) {
    fprintf(stderr, "usage: ./ex6 infile\n");
    return EXIT_FAILURE;
  }

  // Open the input file
  f = fopen(argv[1], "rb");  // "rb" --> read, binary mode
  if (f == NULL) {
    fprintf(stderr, "%s -- ", argv[1]);
    perror("fopen for read failed");
    return EXIT_FAILURE;
  }
  // Change file position indicator to end
  fseek(f, 0, SEEK_END);

  // Get file size
  lSize = ftell(f);
  if (lSize == -1) {
    perror("ftell failed");
    return EXIT_FAILURE;
  }

  // Go through file reading one byte at a time
  // Move position indicator back each time
  char byteRead;
  for (int64_t i = lSize - 1; i >=0; i--) {
    fseek(f, i, SEEK_SET);
    fread((void*) &byteRead, sizeof(char), 1, f);
    printf("%c", byteRead);
  }

  // Test to see if we encountered an error while reading.
  if (ferror(f)) {
    perror("fread failed");
    return EXIT_FAILURE;
  }
  fclose(f);

  return EXIT_SUCCESS;
}
