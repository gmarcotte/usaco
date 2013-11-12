/*
ID: garrett2
LANG: C
TASK: barn1
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
  return *((int *)a) - *((int *)b);
}

int main() {
  int i;
  FILE *fin = fopen("barn1.in", "r");
  
  int M, S, C;
  fscanf(fin, "%d %d %d", &M, &S, &C);
  
  int *occupied = (int *)malloc(C * sizeof(int));
  for (i = 0; i < C; i++) {
    fscanf(fin, "%d", &occupied[i]);
  }
  fclose(fin);

  // Sort the C array
  qsort(occupied, C, sizeof(int), cmp);
  
  // Now get all of the gap sizes between occupied stalls and sort them in
  // descending order.  We store the gaps as negative numbers so that we
  // can reuse our cmp function and still get desc order of magnitude.
  int *gaps = (int *)malloc((C - 1) * sizeof(int));
  for (i = 1; i < C; i++) {
    gaps[i - 1] = -1 * (occupied[i] - occupied[i - 1] - 1);
  }
  qsort(gaps, C - 1, sizeof(int), cmp);
  
  int sol = occupied[C - 1] - occupied[0] + 1;
  for (i = 2; i <= M && i <= C; i++) {
    // Addition because we stored the gaps as negative numbers
    sol += gaps[i - 2];
  }
  

  FILE *fout = fopen("barn1.out", "w");
  fprintf(fout, "%d\n", sol);
  fclose(fout);

  // Clean up allocated memory...
  free(occupied);
  free(gaps);
  
  exit(EXIT_SUCCESS);
}

