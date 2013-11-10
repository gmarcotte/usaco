/*
ID: garrett2
LANG: C
TASK: beads
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  RED,
  BLUE,
  WHITE,
  INVALID_COLOR
} COLOR;

typedef struct NODE NODE;
struct NODE {
  NODE *next;
  NODE *previous;
  COLOR color;
  int count;
};

COLOR charToColor(char c) {
  switch (c) {
    case 'r':
      return RED;
      
    case 'b':
      return BLUE;
      
    case 'w':
      return WHITE;
      
    default:
      return INVALID_COLOR;
  }
}

NODE* makeNewNode() {
  NODE *curr_node = malloc(sizeof(NODE));
  curr_node->count = 0;
  curr_node->next = NULL;
  curr_node->previous = NULL;
  curr_node->color = INVALID_COLOR;
  return curr_node;
}

NODE* freeNode(NODE *node) {
  if (node == NULL) {
    return NULL;
  }
  
  NODE *next = NULL;
  if (node->next != node) {
    next = node->next;
    next->previous = node->previous;
    node->previous->next = next;
  }
  
  free(node);
  return next;
}

// Adds a new empty node following the given node and returns a pointer to it
NODE* appendNewNode(NODE *node) {
  NODE *new_node = makeNewNode();
  if (node == NULL) {
    // We're starting a new cycle, make this node self-referential
    new_node->previous = new_node;
    new_node->next = new_node;
  } else {
    // Add the new node into the given cycle
    new_node->previous = node;
    new_node->next = node->next;
    node->next->previous = new_node;
    node->next = new_node;
  }
  return new_node;
}

int colorsEquivalent(COLOR a, COLOR b) {
  return a == WHITE || b == WHITE || a == b;
}

// Gives the value of splitting the chain
int splitValue(NODE *node) {
  if (node == NULL) {
    return 0;
  }
  
  // Special case 1- and 2-node chains
  if (node->next == node) {
    return node->count;
  }
  
  if (node->next == node->previous) {
    return node->count + node->next->count;
  }
  
  int value = 0;
  NODE *left = node->previous;
  NODE *right = node;
  
  COLOR left_color = node->previous->color;
  COLOR right_color = node->color;
  
  while (left != right) {
    if (colorsEquivalent(left->color, left_color)) {
      if (left_color == WHITE) {
        left_color = left->color;
      }
      value += left->count;
      left = left->previous;
    } else {
      left = left->next;
      break;
    }
  }
  
  while (left != right) {
    if (colorsEquivalent(right->color, right_color)) {
      if (right_color == WHITE) {
        right_color = right->color;
      }
      value += right->count;
      right = right->next;
    } else {
      break;
    }
  }
  
  return value;
}

int main() {
  int i; // List indices
  
  FILE *fin = fopen("beads.in", "r");
  
  int num;
  fscanf(fin, "%d\n", &num);
  
  NODE *curr_node = appendNewNode(NULL);
  
  for (i = 0; i < num; i++) {
    char new_char;
    fscanf(fin, "%c", &new_char);
    
    COLOR new_color = charToColor(new_char);
    if (new_color == INVALID_COLOR) {
      printf("Encountered unexpected char: %c\n", new_char);
      exit(EXIT_FAILURE);
    }
    
    // Check if this is the first bead in the current node
    if (curr_node->color == INVALID_COLOR) {
      curr_node->color = new_color;
      curr_node->count++;
      continue;
    }
    
    // Check if we can add this bead to the current node
    if (curr_node->color == new_color) {
      curr_node->count++;
      continue;
    }
    
    // We need to start a new node
    curr_node = appendNewNode(curr_node);
    curr_node->count++;
    curr_node->color = new_color;
  }
  fclose(fin);

  // Now that we have a circular linked list of nodes, we check each possible
  // split point and pick the max
  int curr_max = 0;
  NODE *start = curr_node;
  do {
    int split = splitValue(curr_node);
    if (split > curr_max) {
      curr_max = split;
    }
    curr_node = curr_node->next;
  } while (start != curr_node);

  FILE *fout = fopen("beads.out", "w");
  fprintf(fout, "%d\n", curr_max);
  fclose(fout);

  // Clean up allocated memory...
  while (curr_node != NULL) {
    curr_node = freeNode(curr_node);
  }
}

