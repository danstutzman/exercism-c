#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_count.h"

#define DEBUG 0

int word_count(const char *input_text, word_count_word_t * words) {
  if (DEBUG) {
    printf("input_text: %s\n", input_text);
  }

  memset(words, 0, sizeof(word_count_word_t) * MAX_WORDS);

  const char* start_of_word = input_text;
  int current_word_len = 0;
  int num_words_so_far = 0;
  while (1) {
    char c = start_of_word[current_word_len];
    if (c == ' ' || c == '\0' || c == ',') {
      int found_word = 0;
      for (int i = 0; i < num_words_so_far; i++) {
        if (strncmp(words[i].text, start_of_word, current_word_len) == 0) {
          strncpy(words[i].text, start_of_word, current_word_len);
          words[i].text[current_word_len] = '\0';
          words[i].count += 1;
          found_word = 1;
          break;
        }
      }

      if (!found_word) {
        strncpy(words[num_words_so_far].text, start_of_word, current_word_len);
        words[num_words_so_far].text[current_word_len] = '\0';
        words[num_words_so_far].count = 1;
        num_words_so_far += 1;
      }

      start_of_word += current_word_len + 1;
      current_word_len = 0;

      if (c == '\0') {
        break;
      }
    } else {
      current_word_len += 1;
    }
  }

  if (DEBUG) {
    for (int i = 0; i < num_words_so_far; i++) {
      printf("words[%d].count = %d\n", i, words[i].count);
      printf("words[%d].text = %s\n", i, words[i].text);
    }
  }

  return num_words_so_far;
}

//int main() { printf("test\n"); }
