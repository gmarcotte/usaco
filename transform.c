/*
ID: garrett2
LANG: C
TASK: transform
*/

#include <stdio.h>
#include <stdlib.h>

char** makeSquare(int N) {
  char **new = (char**)malloc(N * sizeof(char*));
  int i;
  for (i = 0; i < N; i++) {
    new[i] = (char*)malloc(N * sizeof(char));
  }
  return new;
}

void freeSquare(char **square, int N) {
  int i;
  for (i = 0; i < N; i++) {
    free(square[i]);
    square[i] = NULL;
  }
  free(square);
}

void setTransformMatrix(int **tmat, int ii, int ij, int ji, int jj) {
  tmat[0][0] = ii;
  tmat[0][1] = ij;
  tmat[1][0] = ji;
  tmat[1][1] = jj;
}

void idxToCart(int i, int j, int N, int *x, int *y) {
  if (N % 2 == 1) {
    *x = j - N / 2;
    *y = -i + N / 2;
  } else {
    *x = 2 * j - (N - 1);
    *y = -2 * i + (N - 1);
  }
}

void cartToIdx(int x, int y, int N, int *i, int *j) {
  if (N % 2 == 1) {
    *i = N / 2 - y;
    *j = x + N / 2;
  } else {
    *i = (N - 1 - y) / 2;
    *j = (N - 1 + x) / 2;
  }
}

int sameUnderTransformation(char **pre, char **post, int N, int **tmat) {
  int i, j;
  int i2, j2;
  int x, y;
  int x2, y2;
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      idxToCart(i, j, N, &x, &y);
      x2 = tmat[0][0]*x + tmat[0][1]*y;
      y2 = tmat[1][0]*x + tmat[1][1]*y;
      cartToIdx(x2, y2, N, &i2, &j2);
      if (pre[i][j] != post[i2][j2]) {
        return 0;
      }
    }
  }
  return 1;
}

int findTransformation(char **pre, char **post, int N) {
  int **tmat = (int **)malloc(2 * sizeof(int*));
  tmat[0] = (int *)malloc(2 * sizeof(int));
  tmat[1] = (int *)malloc(2 * sizeof(int));
  
  // 90 degree clockwise rotation
  setTransformMatrix(tmat, 0, 1, -1, 0);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 1;
  }
  
  // 180 degree clockwise rotation
  setTransformMatrix(tmat, -1, 0, 0, -1);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 2;
  }
  
  // 270 degree clockwise rotation
  setTransformMatrix(tmat, 0, -1, 1, 0);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 3;
  }
  
  // Horizontal reflection
  setTransformMatrix(tmat, -1, 0, 0, 1);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 4;
  }
  
  // Horizontal reflection + 90 degree rotation
  setTransformMatrix(tmat, 0, 1, 1, 0);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 5;
  }
  
  // Horizontal reflection + 180 degree rotation
  setTransformMatrix(tmat, 1, 0, 0, -1);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 5;
  }
  
  /*
   We can skip this one because it's actually the same as a
   90 degree clockwise rotation.
  // Horizontal reflection + 270 degree rotation
  setTransformMatrix(tmat, 0, 1, -1, 0);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 5;
  }
  */
  
  // No change
  setTransformMatrix(tmat, 1, 0, 0, 1);
  if (sameUnderTransformation(pre, post, N, tmat)) {
    return 6;
  }
  
  return 7;
}

int main() {
  int i, j; // Loop indices
  FILE *fin = fopen("transform.in", "r");
  
  int N;
  fscanf(fin, "%d\n", &N);
  
  char **pre, **post;
  pre = makeSquare(N);
  post = makeSquare(N);
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      fscanf(fin, "%c", &pre[i][j]);
    }
    fscanf(fin, "\n");
  }
  
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      fscanf(fin, "%c", &post[i][j]);
    }
    fscanf(fin, "\n");
  }
  fclose(fin);
  
  int transform = findTransformation(pre, post, N);

  FILE *fout = fopen("transform.out", "w");
  fprintf(fout, "%d\n", transform);
  fclose(fout);

  // Clean up allocated memory...
  freeSquare(pre, N);
  pre = NULL;
  freeSquare(post, N);
  post = NULL;
  
  exit(EXIT_SUCCESS);
}

