#include "aoc_011.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int aoc_011_main(void) {
  FILE *pFile;
  unsigned short lineMax = 255;
  char line[lineMax];

  pFile = fopen("./2023-01-1.txt", "r");

  if (pFile == NULL) {
    perror("Error opening file.");
    return 1;
  }

  unsigned long long sum = 0;
  while (fgets(line, lineMax, pFile)) {
    size_t length = strlen(line);
    char firstDigit = aoc_011_findFirstDigit(line, length);
    char lastDigit = aoc_011_findLastDigit(line, length);

    if (firstDigit == '\0')
      continue;

    unsigned short firstNumber = firstDigit - '0';
    unsigned short lastNumber = lastDigit - '0';

    unsigned short number = firstNumber * 10 + lastNumber;
    sum += number;

    // printf("%c%c | %d | %llu | %s", firstDigit, lastDigit, number, sum,
    // line);
  }

  fclose(pFile);

  printf("Result: %llu\n", sum);

  return 0;
}

char aoc_011_findLastDigit(char *string, size_t length) {
  char digit = '\0';

  char item = '\0';
  size_t index;
  for (index = length - 1; index >= 0; index--) {
    item = string[index];
    if (item < '0')
      continue;
    if (item > '9')
      continue;

    digit = item;
    break;
  }

  return digit;
}

char aoc_011_findFirstDigit(char *string, size_t length) {
  char digit = '\0';

  char item = '\0';
  size_t index;
  for (index = 0; index < length; index++) {
    item = string[index];
    if (item < '0')
      continue;
    if (item > '9')
      continue;

    digit = item;
    break;
  }

  return digit;
}
