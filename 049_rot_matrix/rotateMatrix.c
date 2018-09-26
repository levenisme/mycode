#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rotate(char array[][10]) {
  char oldArray[10][10];
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) {
      oldArray[i][j] = array[i][j];
    }
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      array[i][j] = oldArray[9 - j][i];
}
int main(int argc, char ** argv) {
  if (argc != 2 || argv[0] == NULL || argv[1] == NULL || *argv[1] == '\0') {
    fprintf(stderr, "only have one argv");
    return EXIT_FAILURE;
  }
  char array[10][10];
  char c;
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("could not open file");
    return EXIT_FAILURE;
  }
  int column, row;
  column = row = 0;

  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      array[row][column] = c;
      column++;
    }
    else {
      if (column != 10) {
        perror(" array[row][column]=c; Error!!!\n");
        return EXIT_FAILURE;
      }
      else {
        row++;
        column = 0;
      }
    }
  }
  if (row != 10) {
    perror("row != 10 :Error!!!\n");
    return EXIT_FAILURE;
  }

  rotate(array);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", array[i][j]);
    }
    printf("\n");
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
