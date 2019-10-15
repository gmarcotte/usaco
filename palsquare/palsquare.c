/*
ID: garrett2
LANG: C
TASK: palsquare
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_N 1
#define MAX_N 300

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
  FILE *fin = fopen("palsquare.in", "r");
  
  int base;
  fscanf(fin, "%d", &base);
  
  fclose(fin);

  FILE *fout = fopen("palsquare.out", "w");
  
  char numrep[10];
  char sqrep[20];
  int i;
  for (i = MIN_N; i <= MAX_N; i++) {
    decToBase(i*i, base, sqrep);
    if (isPalindrome(sqrep)) {
      decToBase(i, base, numrep);
      fprintf(fout, "%s %s\n", numrep, sqrep);
    }
  }
  
  fclose(fout);
  exit(EXIT_SUCCESS);
}

