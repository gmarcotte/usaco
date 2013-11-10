/*
ID: garrett2
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 15

// Find the index of a given name in a list of names, or -1 if it isn't there
// Linear Scan - could improve with BST, Trie, or Hashmap
int findName(char *name, char **names, int num_names) {
    int i;
    for (i = 0; i < num_names; i++) {
        if (!strcmp(name, names[i])) {
            return i;
        }
    }
    return -1;
}

int main() {
    int i, j; // Loop indices
    
    FILE *fin = fopen("gift1.in", "r");
    if (!fin) {
        printf("Failed to open gift1.in\n");
        exit(EXIT_FAILURE);
    }
    
    // Read in the first line
    int num_people;
    fscanf(fin, "%d", &num_people);
    
    // Create storage for the names and account values
    char **names = malloc(num_people * sizeof(char *));
    int *accounts = malloc(num_people * sizeof(int));
    
    // Initialize the allocated memory
    for (i = 0; i < num_people; i++) {
        names[i] = malloc(MAX_NAME * sizeof(char));
        for (j = 0; j < MAX_NAME; j++) {
            names[i][j] = '\0';
        }
        accounts[i] = 0;
    }
    
    // Read in the names
    for (i = 0; i < num_people; i++) {
        fscanf(fin, "%s", names[i]);
    }
    
    // Read in the rest of the gift amounts and update accounts along the way
    for (i = 0; i < num_people; i++) {
        char giver_name[MAX_NAME];
        fscanf(fin, "%s", giver_name);
        
        int giver_index = findName(giver_name, names, num_people);
        if (giver_index < 0) {
            printf("Got unexpected giver name: %s\n", giver_name);
            exit(EXIT_FAILURE);
        }
        
        int start, num_gifts;
        fscanf(fin, "%d %d", &start, &num_gifts);
        
        if (num_gifts == 0) {
            // If no gifts to give, just continue
            continue;
        }
        
        int to_give = start / num_gifts;
        for (j = 0; j < num_gifts; j++) {
            char recipient_name[MAX_NAME];
            fscanf(fin, "%s", recipient_name);
            int recipient_index = findName(recipient_name, names, num_people);
            if (recipient_index < 0) {
                printf("Got unexpected recipient name: %s\n", recipient_name);
            }
            accounts[giver_index] -= to_give;
            accounts[recipient_index] += to_give;
        }
    }
    
    // Write the final account values to the output file
    FILE *fout = fopen("gift1.out", "w");
    for (i = 0; i < num_people; i++) {
        fprintf(fout, "%s %d\n", names[i], accounts[i]);
    }
    
    
    // Free everything
    for (i = 0; i < num_people; i++) {
        free(names[i]);
        names[i] = NULL;
    }
    free(names);
    names = NULL;
    free(accounts);
    accounts = NULL;
    exit(EXIT_SUCCESS);
}
