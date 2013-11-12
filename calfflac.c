/*
ID: garrett2
LANG: C
TASK: calfflac
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 20000
#define MAX_PAL_LEN 2000

char toLower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 'a';
  } else {
    return c;
  }
}

int isChar(char c) {
  return (c >= 'a' && c <= 'z');
}

int isPalindrome(char *str, int left, int right) {
  if (!isChar(toLower(str[left])) || !isChar(toLower(str[right]))) {
    return 0;
  }
  
  int found_char = 0;
  while (left <= right) {
    char l = toLower(str[left]);
    if (!isChar(l)) {
      left++;
      continue;
    }
    
    char r = toLower(str[right]);
    if (!isChar(r)) {
      right--;
      continue;
    }
    
    found_char++;
    if (left != right) {
      found_char++;
    }
    
    if (r != l) {
      return 0;
    }
    left++;
    right--;
  }
  return found_char;
}

int min(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

void longestPal(char *str, int left, int right, int curr_max, int *pal_left, int *pal_right, int *pal_len) {
  int i, j;
  int max_left = 0;
  int max_right = 0;
  int max_len = curr_max;
  int curr_len;
  for (i = 0; i <= right; i++) {
    for (j = min(right, i + MAX_PAL_LEN - 1); j >= i; j--) {
      if ((j - i + 1) <= max_len) {
        // Already found a palindrome longer than the rest of the window
        break;
      }
      curr_len = isPalindrome(str, i, j);
      if (curr_len > max_len) {
        max_len = curr_len;
        max_left = i;
        max_right = j;
      }
    }
  }
  *pal_left = max_left;
  *pal_right = max_right;
  *pal_len = max_len;
}

int main() {
  int i; // Loop indices
  
  FILE *fin = fopen("calfflac.in3", "r");
  
  char *str = (char *)malloc(MAX_STR_LEN * sizeof(char));
  for (i = 0; fscanf(fin, "%c", &str[i]) != EOF; i++);
  fclose(fin);
  
  int num_chars = i;
  
  int max_left = 0;
  int max_right = 0;
  int max_len = 1;
  
  if (num_chars <= MAX_STR_LEN) {
    longestPal(str, 0, num_chars - 1, 1, &max_left, &max_right, &max_len);
  } else {
    int pal_left, pal_right, pal_len;
    for (i = 0; i <= num_chars - MAX_PAL_LEN; i++) {
      longestPal(str, i, i + MAX_PAL_LEN - 1, max_len, &pal_left, &pal_right, &pal_len);
      if (pal_len > max_len) {
        max_left = pal_left;
        max_right = pal_right;
        max_len = pal_len;
      }
    }
  }

  FILE *fout = fopen("calfflac.out", "w");
  fprintf(fout, "%d\n", max_len);
  for (i = max_left; i <= max_right; i++) {
    fprintf(fout, "%c", str[i]);
  }
  fprintf(fout, "\n");
  fclose(fout);

  // Clean up allocated memory...
  free(str);
  
  exit(EXIT_SUCCESS);
}

