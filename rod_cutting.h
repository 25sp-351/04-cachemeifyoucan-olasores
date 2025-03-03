#ifndef ROD_CUTTING_H
#define ROD_CUTTING_H

#define MAX_PIECES 100
#define MAX_LENGTH 10000
#define CACHE_SIZE 1000

typedef struct {
    int length;
    int value;
} Piece;

typedef struct {
    int length;
    int value;
    int *cuts;
    int num_cuts;
    int access_count;
    int last_access;
} CacheEntry;

typedef struct {
    CacheEntry entries[CACHE_SIZE];
    int size;
    int clock;
} Cache;

// Function declarations
void read_input_file(const char *filename, Piece *pieces, int *piece_count);
int process_rod_length(int length, Piece *pieces, int piece_count, Cache *cache);
void print_solution(int length, int value, Piece *pieces, int *cuts, int num_cuts);
void cache_result(Cache *cache, int length, int value, int *cuts, int num_cuts);
void init_cache(Cache *cache);

#endif 