#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_count.h"

#define DEBUG 1

int word_count(const char *input_text, word_count_word_t * words) {
  if (DEBUG) {
    printf("input_text: %s\n", input_text);
  }

  const char* start_of_word = input_text;
  int current_word_len = 0;
  int num_word = 0;
  while (1) {
    char c = start_of_word[current_word_len];
    //printf("num_word=%d current_word_len=%d c=%c\n",
    //    num_word, current_word_len, c);
    if (c == ' ' || c == '\0') {
      strncpy(words[num_word].text, start_of_word, current_word_len);
      words[num_word].text[current_word_len] = '\0';
      words[num_word].count = 1;

      if (c == '\0') {
        break;
      } else {
        num_word += 1;
        start_of_word += current_word_len + 1;
        current_word_len = 0;
      }
    } else {
      //words[num_word].text[offset_into_word] = input_text[offset];
      current_word_len += 1;
    }
  }
  int num_words = num_word + 1;

  if (DEBUG) {
    for (int i = 0; i < num_words; i++) {
      printf("words[%d].count = %d\n", i, words[i].count);
      printf("words[%d].text = %s\n", i, words[i].text);
    }
  }

  return num_words;
}

//int main() { printf("test\n"); }
