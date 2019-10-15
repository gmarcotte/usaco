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

int maxPal1(char *norm, int i, int len) {
  int max = 1;
  int l = i - 1;
  int r = i + 1;
  while (l >= 0 && r < len && norm[l] == norm[r]) {
    max += 2;
    l--;
    r++;
  }
  return max;
}

int maxPal2(char *norm, int i, int len) {
  int max = 2;
  int l = i - 1;
  int r = i + 2;
  while (l >= 0 && r < len && norm[l] == norm[r]) {
    max += 2;
    l--;
    r++;
  }
  return max;
}

int min(int a, int b) {
  if (a > b) {
    return b;
  } else {
    return a;
  }
}

int main() {
  int i; // Loop indices
  
  FILE *fin = fopen("calfflac.in", "r");
  char *str = (char *)malloc(MAX_STR_LEN * sizeof(char));
  char *norm = (char *)malloc(MAX_STR_LEN * sizeof(char));
  
  char newchar;
  int str_len = 0;
  int num_chars = 0;
  while (1) {
    if (fscanf(fin, "%c", &newchar) == EOF) {
      break;
    }
    str[str_len++] = newchar;
    if (isChar(toLower(newchar))) {
      norm[num_chars++] = toLower(newchar);
    }
  }
  fclose(fin);
  
  int max_left = 0;
  int max_len = 1;
  int tmp_len, tmp_left;
  for (i = 0; i < num_chars; i++) {
    tmp_len = maxPal1(norm, i, num_chars);
    tmp_left = i - tmp_len / 2;
    if (tmp_len > max_len) {
      max_left = tmp_left;
      max_len = tmp_len;
    } else if (tmp_len == max_len) {
      max_left = min(max_left, tmp_left);
    }
    if (i < num_chars - 1 && norm[i] == norm[i+1]) {
      tmp_len = maxPal2(norm, i, num_chars);
      tmp_left = i - (tmp_len - 1) / 2;
      if (tmp_len > max_len) {
        max_left = tmp_left;
        max_len = tmp_len;
      } else if (tmp_len == max_len) {
        max_left = min(max_left, tmp_left);
      }
    }
  }
  
  FILE *fout = fopen("calfflac.out", "w");
  fprintf(fout, "%d\n", max_len);
  i = -1;
  int j;
  for (j = 0; j < str_len; j++) {
    if (isChar(toLower(str[j]))) {
      i++;
    }
    if (i >= max_left) {
      fprintf(fout, "%c", str[j]);
    }
    if (i == max_left + max_len - 1) {
      break;
    }
  }
  fprintf(fout, "\n");
  fclose(fout);

  // Clean up allocated memory...
  free(str);
  free(norm);
  
  exit(EXIT_SUCCESS);
}

