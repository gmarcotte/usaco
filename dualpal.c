/*
ID: garrett2
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_BASE 2
#define MAX_BASE 10

int isPalindrome(char *str) {
  int left = 0;
  int right = 0;
  while (str[right] != '\0') {
    right++;
  }
  right--;
  
  while (left < right) {
    if (str[left] != str[right]) {
      return 0;
    }
    left++;
    right--;
  }
  return 1;
}

char charRep(int val) {
  if (val < 10) {
    return '0' + val;
  } else {
    return 'A' + val - 10;
  }
}

void decToBase(int val, int base, char *out) {
  int maxpower = 1;
  int cnt = 0;
  while (maxpower <= val) {
    maxpower *= base;
    cnt++;
  }
  maxpower /= base;
  cnt--;
  
  int i = 0;
  while (cnt >= 0) {
    int digval;
    if (val == 0) {
      digval = 0;
    } else {
      digval = val / maxpower;
      val -= digval * maxpower;
      maxpower /= base;
    }
    out[i] = charRep(digval);
    cnt--;
    i++;
  }
  out[i] = '\0';
}

int main() {
  FILE *fin = fopen("dualpal.in", "r");
  
  int s, n;
  fscanf(fin, "%d %d", &n, &s);
  
  fclose(fin);
  
  char numrep[40];

  FILE *fout = fopen("dualpal.out", "w");
  
  int i;
  int found = 0;
  while (found < n) {
    s++;
    int numpal = 0;
    for (i = MIN_BASE; i <= MAX_BASE; i++) {
      decToBase(s, i, numrep);
      if (isPalindrome(numrep)) {
        numpal++;
      }
      if (numpal >= 2) {
        fprintf(fout, "%d\n", s);
        found++;
        break;
      }
    }
  }
  
  fclose(fout);
  exit(EXIT_SUCCESS);
}

