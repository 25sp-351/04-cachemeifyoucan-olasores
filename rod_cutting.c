#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rod_cutting.h"

void init_cache(Cache *cache) {
    cache->size = 0;
    cache->clock = 0;
}

void read_input_file(const char *filename, Piece *pieces, int *piece_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    *piece_count = 0;
    while (fscanf(file, "%d,%d", &pieces[*piece_count].length, 
                 &pieces[*piece_count].value) == 2) {
        (*piece_count)++;
    }

    fclose(file);
}

int process_rod_length(int length, Piece *pieces, int piece_count, Cache *cache) {
    for (int i = 0; i < cache->size; i++) {
        if (cache->entries[i].length == length) {
            print_solution(length, cache->entries[i].value, pieces, 
                         cache->entries[i].cuts, cache->entries[i].num_cuts);
            return cache->entries[i].value;
        }
    }

    int *dp = malloc((length + 1) * sizeof(int));
    int *choice = malloc((length + 1) * sizeof(int));
    int *cuts = malloc(length * sizeof(int));
    int num_cuts = 0;

    for (int i = 0; i <= length; i++) {
        dp[i] = 0;
        choice[i] = -1;
    }

    for (int i = 1; i <= length; i++) {
        for (int j = 0; j < piece_count; j++) {
            if (pieces[j].length <= i) {
                int val = pieces[j].value + dp[i - pieces[j].length];
                if (val > dp[i]) {
                    dp[i] = val;
                    choice[i] = j;
                }
            }
        }
    }

    int curr_len = length;
    while (curr_len > 0 && choice[curr_len] != -1) {
        cuts[num_cuts++] = choice[curr_len];
        curr_len -= pieces[choice[curr_len]].length;
    }

    cache_result(cache, length, dp[length], cuts, num_cuts);

    print_solution(length, dp[length], pieces, cuts, num_cuts);

    free(dp);
    free(choice);
    free(cuts);

    return dp[length];
}

void print_solution(int length, int value, Piece *pieces, int *cuts, int num_cuts) {
    int counts[MAX_PIECES] = {0};
    int remainder = length;
    
    for (int i = 0; i < num_cuts; i++) {
        counts[cuts[i]]++;
        remainder -= pieces[cuts[i]].length;
    }

    for (int i = 0; i < MAX_PIECES; i++) {
        if (counts[i] > 0) {
            printf("%d @ %d = %d\n", counts[i], pieces[i].length, 
                   pieces[i].value * counts[i]);
        }
    }
    printf("Remainder: %d\n", remainder);
    printf("Value: %d\n", value);
    printf("\n");
}