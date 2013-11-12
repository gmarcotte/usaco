/*
ID: garrett2
LANG: C
TASK: crypt1
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  FILE *fin = fopen("crypt1.in", "r");
  int N;
  fscanf(fin, "%d", &N);
  int *digs = (int *)malloc(N * sizeof(int));
  int diglookup[10] = {0};
  for (i = 0; i < N; i++) {
    fscanf(fin, "%d", &digs[i]);
    diglookup[digs[i]] = 1;
  }
  fclose(fin);

  int sols = 0;
  int a, b, c, d, e;
  int abc;
  int de;
  int tmp;
  
  for (a = 0; a < N; a++) {
    for (b = 0; b < N; b++) {
      for (c = 0; c < N; c++) {
        for (d = 0; d < N; d++) {
          for (e = 0; e < N; e++) {
            abc = 100 * digs[a] + 10 * digs[b] + digs[c];
            de = 10 * digs[d] + digs[e];
            
            tmp = abc * digs[e];
            if (tmp >= 1000) {
              continue;
            }
            
            if (!diglookup[tmp % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/10 % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/100 % 10]) {
              continue;
            }
            
            tmp = abc * digs[d];
            if (!diglookup[tmp % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/10 % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/100 % 10]) {
              continue;
            }
            
            tmp = abc * de;
            if (tmp >= 10000) {
              continue;
            }
            if (!diglookup[tmp % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/10 % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/100 % 10]) {
              continue;
            }
            
            if (!diglookup[tmp/1000 % 10]) {
              continue;
            }
            
            sols++;
          }
        }
      }
    }
  }

  FILE *fout = fopen("crypt1.out", "w");
  fprintf(fout, "%d\n", sols);
  fclose(fout);

  // Clean up allocated memory...
  free(digs);
  
  exit(EXIT_SUCCESS);
}

