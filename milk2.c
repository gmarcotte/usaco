/*
ID: garrett2
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  MILKING,
  NOT_MILKING,
  MILKING_COMPLETE
} STATUS;

typedef struct NODE NODE;
struct NODE {
  NODE *next;
  STATUS isMilking;
  int time;
};

// Frees a given node and returns a pointer to the next node
NODE* freeNode(NODE *node) {
  if (node == NULL) {
    return NULL;
  }
  
  NODE *next = node->next;
  free(node);
  return next;
}

// Given a node, removes and frees the next node, and points the given node
// to the next next node.
void freeNextNode(NODE *node) {
  if (node == NULL) {
    return;
  }
  node->next = freeNode(node->next);
}

void insertMilkingInterval(int start, int end, NODE *root) {
  NODE *new_start = malloc(sizeof(NODE));
  NODE *new_end = malloc(sizeof(NODE));
  new_start->time = start;
  new_start->isMilking = MILKING;
  new_start->next = new_end;
  new_end->time = end;
  new_end->isMilking = NOT_MILKING;
  new_end->next = root->next;
  root->next = new_start;
}

void mergeMilkingInterval(int start, int end, NODE *root) {
  // We walk to the last interval that starts before the given interval
  while (root->next->isMilking != MILKING_COMPLETE &&
         root->next->time < start) {
    root = root->next;
  }
  
  NODE *next = root->next;
  
  // New interval starts beyond the known range of milking times, extend it
  if (next->isMilking == MILKING_COMPLETE && next->time <= start) {
    if (root->isMilking == MILKING) {
      NODE *new_start = malloc(sizeof(NODE));
      new_start->isMilking = NOT_MILKING;
      new_start->time = next->time;
      new_start->next = next;
      next->time = end;
      root->next = new_start;
    } else {
      next->time = end;
    }
    mergeMilkingInterval(start, end, root);
    return;
  }
  
  
  // New interval is contained by an existing milking interval
  if (next->time >= end && root->isMilking == MILKING) {
    return;
  }
  
  // New interval butts up against the next interval
  if (next->time == end && root->isMilking == NOT_MILKING) {
    if (root->next->isMilking == MILKING) {
      root->next->time = start;
      return;
    } else if (root->next->isMilking == MILKING_COMPLETE) {
      NODE *new_start = malloc(sizeof(NODE));
      new_start->next = root->next;
      new_start->isMilking = MILKING;
      new_start->time = start;
      root->next = new_start;
      return;
    }
  }
  
  // New interval is contained by an existing non-milking interval, need to
  // create a new milking interval.
  if (next->time > end && root->isMilking == NOT_MILKING) {
    insertMilkingInterval(start, end, root);
    return;
  }
  
  // If we have overlap, we free nodes until we don't, then fix the invariant
  while (root->next->isMilking != MILKING_COMPLETE && root->next->time < end) {
    freeNextNode(root);
  }
  
  next = root->next;
  
  // New interval ends beyond known range of milking times, extend it
  if (next->isMilking == MILKING_COMPLETE) {
    NODE *new_start = malloc(sizeof(NODE));
    new_start->isMilking = NOT_MILKING;
    new_start->time = next->time;
    new_start->next = next;
    next->time = end;
    root->next = new_start;
  }
  
  if (root->isMilking == root->next->isMilking) {
    // We broke the invariant, just merge the two intervals with same status
    freeNextNode(root);
  }
  
  // Now we can insert our interval without overlap
  mergeMilkingInterval(start, end, root);
}

int main() {
  int i = 0; // List indices
  FILE *fin = fopen("milk2.in", "r");
  
  // Set up the initial list with the start and end nodes.  End is set to 0,
  // it will be updated as we go along.  The entire interval is currently not
  // milking.
  NODE *start = malloc(sizeof(NODE));
  NODE *end = malloc(sizeof(NODE));
  start->next = end;
  start->isMilking = NOT_MILKING;
  start->time = 0;
  end->next = NULL;
  end->isMilking = MILKING_COMPLETE;
  end->time = 0;
  
  int num;
  fscanf(fin, "%d", &num);
  
  for (i = 0; i < num; i++) {
    // Read in the milking times
    int start_time, end_time;
    fscanf(fin, "%d %d", &start_time, &end_time);
    
    // Now merge the milking interval into the list
    mergeMilkingInterval(start_time, end_time, start);
  }
  
  fclose(fin);

  // Now we walk through the interval list to find the longest milking and
  // non-milking times
  NODE *curr = start;
  int max_milking = 0;
  int max_non_milking = 0;
  while (curr->isMilking != MILKING_COMPLETE) {
    int duration = curr->next->time - curr->time;
    if (curr->isMilking == MILKING && duration > max_milking) {
      max_milking = duration;
    }
    
    if (curr->isMilking == NOT_MILKING &&
        duration > max_non_milking &&
        max_milking > 0) {
      max_non_milking = duration;
    }
    
    curr = curr->next;
  }

  FILE *fout = fopen("milk2.out", "w");
  fprintf(fout, "%d %d\n", max_milking, max_non_milking);
  fclose(fout);

  // Clean up allocated memory...
  while (start != NULL) {
    start = freeNode(start);
  }
  
  exit(EXIT_SUCCESS);
}

