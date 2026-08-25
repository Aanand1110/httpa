#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

static unsigned int hash(const char* key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASHMAP_CAPACITY;
}

hashmap_t* hashmap_create(void) {
    hashmap_t* map = malloc(sizeof(hashmap_t));
    if (!map) return NULL;
    map->count = 0;
    for (size_t i = 0; i < HASHMAP_CAPACITY; i++) {
        map->entries[i].key = NULL;
        map->entries[i].value = NULL;
    }
    return map;
}

void hashmap_destroy(hashmap_t* map) {
    if (!map) return;
    for (size_t i = 0; i < HASHMAP_CAPACITY; i++) {
        free(map->entries[i].key);
        free(map->entries[i].value);
    }
    free(map);
}

int hashmap_set(hashmap_t* map, const char* key, const char* value) {
    if (!map || !key || !value) return -1;
    if (map->count >= HASHMAP_CAPACITY) return -1;

    unsigned int idx = hash(key);
    size_t start = idx;

    do {
        if (map->entries[idx].key == NULL) {
            map->entries[idx].key = strdup(key);
            map->entries[idx].value = strdup(value);
            if (!map->entries[idx].key || !map->entries[idx].value) {
                free(map->entries[idx].key);
                free(map->entries[idx].value);
                return -1;
            }
            map->count++;
            return 0;
        }
        if (strcmp(map->entries[idx].key, key) == 0) {
            return -1;
        }
        idx = (idx + 1) % HASHMAP_CAPACITY;
    } while (idx != start);

    return -1;
}

char* hashmap_get(hashmap_t* map, const char* key) {
    if (!map || !key) return NULL;

    unsigned int idx = hash(key);
    size_t start = idx;

    do {
        if (map->entries[idx].key == NULL) {
            return NULL;
        }
        if (strcmp(map->entries[idx].key, key) == 0) {
            return map->entries[idx].value;
        }
        idx = (idx + 1) % HASHMAP_CAPACITY;
    } while (idx != start);

    return NULL;
}

int hashmap_remove(hashmap_t* map, const char* key) {
    if (!map || !key) return -1;

    unsigned int idx = hash(key);
    size_t start = idx;

    do {
        if (map->entries[idx].key == NULL) {
            return -1;
        }
        if (strcmp(map->entries[idx].key, key) == 0) {
            free(map->entries[idx].key);
            free(map->entries[idx].value);
            map->entries[idx].key = NULL;
            map->entries[idx].value = NULL;
            map->count--;
            return 0;
        }
        idx = (idx + 1) % HASHMAP_CAPACITY;
    } while (idx != start);

    return -1;
}

size_t hashmap_size(hashmap_t* map) {
    return map ? map->count : 0;
}