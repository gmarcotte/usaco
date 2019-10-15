/*
ID: garrett2
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE NODE;
struct NODE {
  NODE *next;
  NODE *previous;
  int isMilking;
  int time;
};

// Frees a given node and returns a pointer to the next node
NODE* freeNode(NODE *node) {
  if (node == NULL) {
    return NULL;
  }
  
  NODE *next = node->next;
  free(node);
  if (next) {
    next->previous = NULL;
  }
  return next;
}

// Given a node, removes and frees the next node, and points the given node
// to the next next node.
void freeNextNode(NODE *node) {
  if (node == NULL) {
    return;
  }
  node->next = freeNode(node->next);
  if (node->next) {
    node->next->previous = node;
  }
}

void insertMilkingInterval(int start, int end, NODE *root) {
  NODE *new_start = malloc(sizeof(NODE));
  NODE *new_end = malloc(sizeof(NODE));
  new_start->time = start;
  new_start->isMilking = 1;
  new_start->next = new_end;
  new_start->previous = root;
  new_end->time = end;
  new_end->isMilking = 0;
  new_end->next = root->next;
  new_end->previous = new_start;
  root->next = new_start;
}

/**
 Invariants enforced:
  - last point is always not milking
  - milking and not milking intervals alternate
 */
void mergeMilkingInterval(int start, int end, NODE *root) {
  if (root->next == NULL) {
    if (root->time == start) {
      root->time = end;
    } else {
      insertMilkingInterval(start, end, root);
    }
    return;
  }
  
  while (root->next && root->next->time <= start) {
    root = root->next;
  }

  if (!root->next) {
    mergeMilkingInterval(start, end, root);
    return;
  }
  
  if (root->next->time > end) {
    if (root->isMilking) {
      // pass
    } else if (root->time == start) {
      root->time = end;
    } else {
      insertMilkingInterval(start, end, root);
    }
    return;
  }
  
  if (root->next->time == end) {
    if (!root->isMilking) {
      if (root->time == start) {
        NODE *prev = root->previous;
        freeNextNode(prev);
        freeNextNode(prev);
      } else {
        root->next->time = start;
      }
    }
    return;
  }
  
  while (root->next && root->next->time <= end) {
    freeNextNode(root);
  }
  
  if (root->isMilking) {
    if (!root->next) {
      NODE *new_end = (NODE *)malloc(sizeof(NODE));
      root->next = new_end;
      new_end->time = end;
      new_end->next = NULL;
      new_end->previous = root;
      new_end->isMilking = 0;
    } else if (root->next->isMilking) {
      NODE *new_end = (NODE *)malloc(sizeof(NODE));
      new_end->isMilking = 0;
      new_end->time = end;
      new_end->next = root->next;
      new_end->previous = root;
      root->next->previous = new_end;
      root->next = new_end;
    }
  } else {
    if (!root->next) {
      mergeMilkingInterval(start, end, root);
    } else if (!root->next->isMilking) {
      if (root->time == start) {
        NODE *prev = root->previous;
        freeNextNode(prev);
      } else {
        NODE *new_start = (NODE *)malloc(sizeof(NODE));
        new_start->isMilking = 1;
        new_start->time = start;
        new_start->previous = root;
        new_start->next = root->next;
        root->next->previous= new_start;
        root->next = new_start;
      }
    } else {
      if (root->time == start) {
        root->time = end;
      } else {
        insertMilkingInterval(start, end, root);
      }
    }
  }
}

int main() {
  int i = 0; // List indices
  FILE *fin = fopen("milk2.in", "r");
  
  // Set up the initial node at time -1 so that all future nodes will be
  // after it.
  NODE *start = (NODE *)malloc(sizeof(NODE));
  start->next = NULL;
  start->isMilking = 0;
  start->time = -1;
  
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
  while (curr->next != NULL) {
    int duration = curr->next->time - curr->time;
    if (curr->isMilking && duration > max_milking) {
      max_milking = duration;
    }
    
    if (!curr->isMilking &&
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

