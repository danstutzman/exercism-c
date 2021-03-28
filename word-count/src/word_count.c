#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_count.h"

#define DEBUG 1

int is_punctuation(char c) {
  return c == ' ' ||
         c == '\0' ||
         c == ',' ||
         c == '\n' ||
         c == ':' ||
         c == '!' ||
         c == '@' ||
         c == '$' ||
         c == '%' ||
         c == '^' ||
         c == '&' ||
         c == '.' ||
         c == '\'';
}

int strncmpci(const char * str1, const char * str2, size_t num) {
  int ret_code = 0;
  size_t chars_compared = 0;

  while ((chars_compared < num) && (*str1 || *str2)) {
    ret_code = tolower((int)(*str1)) - tolower((int)(*str2));
    if (ret_code != 0) {
      break;
    }
    chars_compared++;
    str1++;
    str2++;
  }

  return ret_code;
}

void copy_lowercase(char* to, const char* from, int length) {
  for (int i = 0; i < length; i++) {
    to[i] = tolower(from[i]);
  }
  to[length] = '\0';
}

int word_count(const char *input_text, word_count_word_t * words) {
  if (DEBUG) {
    printf("input_text: %s\n", input_text);
  }

  memset(words, 0, sizeof(word_count_word_t) * MAX_WORDS);

  const char* start_of_word = input_text;
  int current_word_len = 0;
  int num_words_so_far = 0;
  int past_initial_whitespace = 0;
  while (1) {
    char c = start_of_word[current_word_len];
    if (is_punctuation(c) && !(c == '\'' && current_word_len > 0 &&
          !is_punctuation(start_of_word[current_word_len + 1]))) {
      if (past_initial_whitespace) {
        if (current_word_len > MAX_WORD_LENGTH) {
          return EXCESSIVE_LENGTH_WORD;
        }

        int found_word = 0;
        for (int i = 0; i < num_words_so_far; i++) {
          if (strncmpci(words[i].text, start_of_word, current_word_len) == 0) {
            copy_lowercase(words[i].text, start_of_word, current_word_len);
            words[i].count += 1;
            found_word = 1;
            break;
          }
        }

        if (!found_word) {
          copy_lowercase(words[num_words_so_far].text, start_of_word,
              current_word_len);
          words[num_words_so_far].count = 1;
          num_words_so_far += 1;
        }
      }

      start_of_word += current_word_len + 1;
      current_word_len = 0;
      past_initial_whitespace = 0;

      if (c == '\0') {
        break;
      }
    } else {
      past_initial_whitespace = 1;
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
