/*
ID: garrett2
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CHAR 'A'
#define MAX_CHAR 'Z'
#define NUM_CHARS (MAX_CHAR - MIN_CHAR + 1)
//#define DICT_FILE "namenum.dict.txt"
#define DICT_FILE "dict.txt"
#define MAX_NAME 13

typedef struct NODE NODE;
struct NODE {
  NODE **children;
  int isWord;
};

NODE* makeNewNode() {
  NODE *new = malloc(sizeof(NODE));
  new->children = malloc(NUM_CHARS * sizeof(NODE*));
  new->isWord = 0;
  
  int i;
  for (i = 0; i < NUM_CHARS; i++) {
    new->children[i] = NULL;
  }
  return new;
}

int charIndex(char c) {
  return c - MIN_CHAR;
}

void insertWord(char *word, NODE *root) {
  char next_char = word[0];
  if (next_char == '\0') {
    root->isWord = 1;
    return;
  }
  
  int index = charIndex(next_char);
  if (root->children[index] == NULL) {
    root->children[index] = makeNewNode();
  }
  
  insertWord(word + 1, root->children[index]);
}

void freeAllNodes(NODE *root) {
  if (root == NULL) {
    return;
  }
  
  int i;
  for (i = 0; i < NUM_CHARS; i++) {
    freeAllNodes(root->children[i]);
    root->children[i] = NULL;
  }
  free(root);
}

char* charsForNum(char num) {
  switch (num) {
    case '2':
      return "ABC";
    
    case '3':
      return "DEF";
      
    case '4':
      return "GHI";
      
    case '5':
      return "JKL";
      
    case '6':
      return "MNO";
      
    case '7':
      return "PRS";
      
    case '8':
      return "TUV";
      
    case '9':
      return "WXY";
      
    default:
      return "";
  }
}

int writeStrings(char *serial, char *output, int i, FILE *fout, NODE *trie) {
  if (serial[i] == '\0') {
    output[i] = '\0';
    if (trie->isWord) {
      fprintf(fout, "%s\n", output);
      return 1;
    }
    return 0;
  }
  
  char c = serial[i];
  char *keys = charsForNum(c);
  
  int j;
  int num = 0;
  for (j = 0; j < 3; j++) {
    int keyIndex = charIndex(keys[j]);
    if (trie->children[keyIndex] != NULL) {
      output[i] = keys[j];
      num += writeStrings(serial, output, i + 1, fout, trie->children[keyIndex]);
    }
  }
  return num;
}

int main() {
  // Build the dictionary trie
  NODE *trie = makeNewNode();
  FILE *fdict = fopen(DICT_FILE, "r");
  char name[MAX_NAME];
  while (fscanf(fdict, "%s", name) != EOF) {
    insertWord(name, trie);
  }
  fclose(fdict);
  
  // Read in the serial number
  char serial[MAX_NAME];
  FILE *fin = fopen("namenum.in", "r");
  fscanf(fin, "%s", serial);
  fclose(fin);

  FILE *fout = fopen("namenum.out", "w");
  
  // Find all valid strings
  char output[MAX_NAME];
  int num = writeStrings(serial, output, 0, fout, trie);
  if (num == 0) {
    fprintf(fout, "NONE\n");
  }
  
  fclose(fout);

  // Clean up allocated memory...
  freeAllNodes(trie);
  
  exit(EXIT_SUCCESS);
}

