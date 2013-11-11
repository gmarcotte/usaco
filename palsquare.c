/*
ID: garrett2
LANG: C
TASK: palsquare
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fin = fopen("palsquare.in", "r");
  // Read file data here...
  fclose(fin);

  // Additional computation here...

  FILE *fout = fopen("palsquare.out", "w");
  // Write solution output here...
  fclose(fout);

  // Clean up allocated memory...
  
  exit(EXIT_SUCCESS);
}

