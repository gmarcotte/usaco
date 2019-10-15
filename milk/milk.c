/*
ID: garrett2
LANG: C
TASK: milk
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
  int *p1 = *((int **)a);
  int *p2 = *((int **)b);
  if (p1[0] > p2[0]) {
    return 1;
  } else if (p1[0] < p2[0]) {
    return -1;
  } else {
    return 0;
  }
}

int main() {
  int i; // List indices
  FILE *fin = fopen("milk.in", "r");
  
  int num_farmers, milk_needed;
  fscanf(fin, "%d %d", &milk_needed, &num_farmers);
  
  int **prices = (int **)malloc(num_farmers * sizeof(int*));
  for (i = 0; i < num_farmers; i++) {
    prices[i] = (int *)malloc(2 * sizeof(int));
    fscanf(fin, "%d %d", &prices[i][0], &prices[i][1]);
  }
  
  fclose(fin);

  // Sort by price
  qsort(prices, num_farmers, sizeof(int*), cmp);
  
  int cost = 0;
  i = 0;
  while (milk_needed > 0) {
    if (prices[i][1] > milk_needed) {
      cost += prices[i][0] * milk_needed;
      milk_needed = 0;
    } else {
      cost += prices[i][0] * prices[i][1];
      milk_needed -= prices[i][1];
    }
    i++;
  }

  FILE *fout = fopen("milk.out", "w");
  fprintf(fout, "%d\n", cost);
  fclose(fout);

  // Clean up allocated memory...
  for (i = 0; i < num_farmers; i++) {
    free(prices[i]);
    prices[i] = NULL;
  }
  free(prices);
  
  exit(EXIT_SUCCESS);
}

