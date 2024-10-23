#include "aoc_012.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZERO_STR "zero"
#define ONE_STR "one"
#define TWO_STR "two"
#define THREE_STR "three"
#define FOUR_STR "four"
#define FIVE_STR "five"
#define SIX_STR "six"
#define SEVEN_STR "seven"
#define EIGHT_STR "eight"
#define NINE_STR "nine"
#define NUMBERS_IN_LETTERS                                                     \
  ((char const *[]){ZERO_STR, ONE_STR, TWO_STR, THREE_STR, FOUR_STR, FIVE_STR, \
                    SIX_STR, SEVEN_STR, EIGHT_STR, NINE_STR})
#define NUMBERS_IN_LETTERS_LENGTH 10
#define LETTERS_IN_NUMBERS ((int[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9})
#define SIZE_T_MAX ((size_t)-1)

int aoc_012_main(void) {
  FILE *pFile;
  char line[255];

  pFile = fopen("./2023-01-1.txt", "r");

  if (pFile == NULL) {
    perror("Error opening file.");
    return 1;
  }

  uint64_t sum = 0;
  while (fgets(line, 255, pFile)) {
    size_t length = strlen(line);
    uint8_t firstNumber = aoc_012_findFirstDigit(line, length);
    uint8_t lastNumber = aoc_012_findLastDigit(line, length);

    uint8_t number = firstNumber * 10 + lastNumber;
    sum += number;

    printf("%d%d | %d | %llu | %s", firstNumber, lastNumber, number, sum, line);
  }

  fclose(pFile);

  printf("Result: %llu\n", sum);

  return 0;
}

uint8_t aoc_012_findFirstDigit(char *string, size_t length) {
  size_t indexOfNumber = SIZE_T_MAX;

  for (size_t index = 0; index < length; index++) {
    char character = string[index];
    if (character < '0' || character > '9')
      continue;

    indexOfNumber = index;
    break;
  }

  size_t indexOfLetters = SIZE_T_MAX;
  size_t lengthOfLetters = 0;

  for (uint8_t index = 0; index < NUMBERS_IN_LETTERS_LENGTH; index++) {
    const char *word = NUMBERS_IN_LETTERS[index];

    char *found = strstr(string, word);
    if (found == NULL)
      continue;

    size_t foundIndex = found - string;
    if (foundIndex >= indexOfLetters)
      continue;

    indexOfLetters = foundIndex;
    lengthOfLetters = strlen(word);
  }

  if (indexOfNumber >= length && indexOfLetters >= length)
    return 0;
  if (indexOfNumber <= indexOfLetters)
    return string[indexOfNumber] - '0';
  if (indexOfLetters >= length)
    return 0;

  char foundedWord[lengthOfLetters + 1];
  strncpy(foundedWord, string + indexOfLetters, lengthOfLetters);
  foundedWord[lengthOfLetters] = '\0';

  for (uint8_t index = 0; index < NUMBERS_IN_LETTERS_LENGTH; index++) {
    const char *word = NUMBERS_IN_LETTERS[index];
    if (strcmp(foundedWord, word) != 0)
      continue;

    return LETTERS_IN_NUMBERS[index];
  }

  return 0;
}

uint8_t aoc_012_findLastDigit(char *string, size_t length) {
  size_t indexOfNumber = SIZE_T_MAX;

  for (int32_t index = length - 1; index >= 0; index--) {
    char character = string[index];
    if (character < '0' || character > '9')
      continue;

    indexOfNumber = index;
    break;
  }

  size_t indexOfLetters = SIZE_T_MAX;
  size_t lengthOfLetters = 0;

  for (int32_t index = length - 1; index >= 0; index--) {
    char substr[length - index + 1];
    strncpy(substr, string + index, length - index);
    substr[length - index] = '\0';

    for (uint8_t i = 0; i < NUMBERS_IN_LETTERS_LENGTH; i++) {
      const char *word = NUMBERS_IN_LETTERS[i];

      char *found = strstr(substr, word);
      if (found == NULL)
        continue;

      indexOfLetters = index;
      lengthOfLetters = strlen(word);
      index = -1;
      break;
    }
  }

  if (indexOfNumber >= length && indexOfLetters >= length)
    return 0;
  if (indexOfNumber >= indexOfLetters || indexOfLetters >= length)
    return string[indexOfNumber] - '0';

  char foundedWord[lengthOfLetters + 1];
  strncpy(foundedWord, string + indexOfLetters, lengthOfLetters);
  foundedWord[lengthOfLetters] = '\0';

  for (uint8_t index = 0; index < NUMBERS_IN_LETTERS_LENGTH; index++) {
    const char *word = NUMBERS_IN_LETTERS[index];
    if (strcmp(foundedWord, word) != 0)
      continue;

    return LETTERS_IN_NUMBERS[index];
  }

  return 0;
}
