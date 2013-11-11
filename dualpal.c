/*
ID: garrett2
LANG: C
TASK: dualpal
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fin = fopen("dualpal.in", "r");
  // Read file data here...
  fclose(fin);

  // Additional computation here...

  FILE *fout = fopen("dualpal.out", "w");
  // Write solution output here...
  fclose(fout);

  // Clean up allocated memory...
  
  exit(EXIT_SUCCESS);
}

