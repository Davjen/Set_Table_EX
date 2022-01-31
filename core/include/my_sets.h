#pragma once
#include <stdlib.h>

typedef struct set_node{
    const char *key;
    size_t key_len;
    struct set_node *next;
    struct set_node *prev;
}set_node_t;

typedef struct set_table{
    set_node_t **nodes;
    size_t hashmap_size;
}set_table_t;


set_table_t *set_table_new(const size_t hashmap_size);
set_node_t *set_insert(set_table_t *table,const char *key, const size_t key_len);
size_t djb33x_hash(const char *key, const size_t keylen);
set_table_t *set_table_search(set_table_t *table, const char *key, const size_t key_len);
set_table_t *set_table_remove(set_table_t *table, const char *key, const size_t key_len);
int set_table_clear(set_table_t *table);