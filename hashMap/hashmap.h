#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

#define HASHMAP_CAPACITY 4

typedef struct {
    char* key;
    char* value;
} hashmap_entry_t;

typedef struct {
    hashmap_entry_t entries[HASHMAP_CAPACITY];
    size_t count;
} hashmap_t;

hashmap_t* hashmap_create(void);
void hashmap_destroy(hashmap_t* map);
int hashmap_set(hashmap_t* map, const char* key, const char* value);
char* hashmap_get(hashmap_t* map, const char* key);
int hashmap_remove(hashmap_t* map, const char* key);
size_t hashmap_size(hashmap_t* map);

#endif
