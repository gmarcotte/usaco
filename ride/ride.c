/*
ID: garrett2
LANG: C
TASK: ride
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 7
#define MOD_VALUE 47

int main() {
    FILE *fin = fopen("ride.in", "r");
    if (fin == NULL) {
        printf("Failed to open ride.in\n");
        exit(EXIT_FAILURE);
    }
    char comet[MAX_LENGTH];
    char group[MAX_LENGTH];
    
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        comet[i] = '\0';
        group[i] = '\0';
    }
    
    int match;
    match = fscanf(fin, "%s", comet);
    if (match == 0) {
        printf("Failed to read comet name\n");
        exit(EXIT_FAILURE);
    }
    
    match = fscanf(fin, "%s", group);
    if (match == 0) {
        printf("Failed to read group name\n");
        exit(EXIT_FAILURE);
    }
    
    int comet_mod = 1;
    int group_mod = 1;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (comet[i] != '\0') {
            comet_mod = (comet_mod * (comet[i] - 'A' + 1)) % MOD_VALUE;
        }
        
        if (group[i] != '\0') {
            group_mod = (group_mod * (group[i] - 'A' + 1)) % MOD_VALUE;
        }
    }
    
    FILE *fout = fopen("ride.out", "w");
    if (comet_mod == group_mod) {
        fprintf(fout, "GO\n");
    } else {
        fprintf(fout, "STAY\n");
    }
    exit(0);
}