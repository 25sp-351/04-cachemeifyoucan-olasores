#include <stdio.h>
#include <stdlib.h>
#include "rod_cutting.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    Piece pieces[MAX_PIECES];
    int piece_count = 0;
    Cache cache;
    
    init_cache(&cache);
    
    read_input_file(argv[1], pieces, &piece_count);
    
    int length;
    while (scanf("%d", &length) == 1) {
        if (length <= 0 || length > MAX_LENGTH) {
            fprintf(stderr, "Invalid length: %d\n", length);
            continue;
        }
        process_rod_length(length, pieces, piece_count, &cache);
    }

    return 0;
} 