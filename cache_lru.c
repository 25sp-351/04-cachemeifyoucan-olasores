#include <stdio.h>
#include <stdlib.h>
#include "rod_cutting.h"

// LRU 
int find_in_cache(Cache *cache, int length) {
    for (int i = 0; i < cache->size; i++) {
        if (cache->entries[i].length == length) {
            cache->entries[i].last_access = ++cache->clock;
            cache->entries[i].access_count++;
            return i;
        }
    }
    return -1;
}

static int find_victim(Cache *cache) {
    int victim = 0;
    int oldest_access = cache->entries[0].last_access;
    
    for (int i = 1; i < cache->size; i++) {
        if (cache->entries[i].last_access < oldest_access) {
            oldest_access = cache->entries[i].last_access;
            victim = i;
        }
    }
    return victim;
}

void cache_result(Cache *cache, int length, int value, int *cuts, int num_cuts) {
    int index;
    
    if (cache->size < CACHE_SIZE) {
        index = cache->size++;
    } else {
        index = find_victim(cache);
        free(cache->entries[index].cuts);
    }
    
    cache->entries[index].length = length;
    cache->entries[index].value = value;
    cache->entries[index].cuts = malloc(num_cuts * sizeof(int));
    cache->entries[index].num_cuts = num_cuts;
    cache->entries[index].last_access = ++cache->clock;
    cache->entries[index].access_count = 1;
    
    for (int i = 0; i < num_cuts; i++) {
        cache->entries[index].cuts[i] = cuts[i];
    }
}