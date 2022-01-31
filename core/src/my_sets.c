#include <string.h>
#include "my_sets.h"


set_table_t *set_table_new(const size_t hashmap_size){
    set_table_t *table = malloc(sizeof(set_table_t));

    if(!table){
        return NULL;
    }

    table->hashmap_size=hashmap_size;
    table->nodes = calloc(table->hashmap_size,sizeof(set_node_t*));

    if(!table->nodes){
        free(table);
        return NULL;
    }
    return table;
}

size_t djb33x_hash(const char *key, const size_t keylen){
    size_t hash=5381;

    for(size_t i = 0; i<keylen; i++){
        hash= ((hash<<5)+hash) ^ key[i];
    }
    return hash;
}

set_node_t *set_insert(set_table_t *table, const char *key, const size_t key_len){
    size_t hash = djb33x_hash(key,key_len);
    size_t index = hash%table->hashmap_size;
    set_node_t *head = table->nodes[index];
    // key = memcpy()

    if(!head){
        table->nodes[index] = malloc(sizeof(set_node_t));
        if(!table->nodes[index]){
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;

        return table->nodes[index];
    }

        set_node_t* tail = head;
        while(head){
            if(head->key_len == key_len && strcmp(key,head->key)==0){
                return NULL;
            }
            tail=head;
            head=head->next;
        }

    set_node_t *new_item = malloc(sizeof(set_node_t));

        if(!new_item){
            return NULL;
        }

        new_item->key=key;
        new_item->key_len=key_len;
        new_item->next=NULL;

        tail->next=new_item;
        new_item->prev = tail;

        return new_item;
    
}

int set_table_clear(set_table_t *table)
{
    if (!table)
    {
        return -1;
    }

    free(table->nodes);
    free(table);

    return 0;
}

set_table_t *set_table_search(set_table_t *table, const char *key, const size_t key_len){
    size_t hash = djb33x_hash(key,key_len);
    size_t index = hash%table->hashmap_size;
    set_node_t *head = table->nodes[index];

    if(!head)return NULL;
    set_node_t *tail=head;
    while(head){
        if(head->key_len == key_len && strcmp(key, head->key) == 0) return head;
        
        tail=head;
        head=head->next;
    }
    return NULL;
}
set_table_t *set_table_remove(set_table_t *table, const char *key, const size_t key_len){
    size_t hash = djb33x_hash(key,key_len);
    size_t index = hash%table->hashmap_size;
    set_node_t *head = table->nodes[index];

    if(!head){
        return NULL;
    }

    set_node_t *tail = head;

    while(head){

        //TO DO->remoce this chance increasing the hasmap size according to the elements.
        if(head->next){
            //theat means more than 1 element per index(hasmapsize too small)
            if(head->key_len == key_len && strcmp(key, head->key) == 0){
                //Need to check if is first element, last element or middle.
                if (!head->prev)
                {
                    head->next->prev = NULL;
                    head->next = NULL;
                }
                else if (!head->next)
                {
                    head->prev->next = NULL;
                    head->prev = NULL;
                }
                else
                {
                    head->prev->next = head->next;
                    head->next->prev = head->prev;
                    head->next = NULL;
                    head->prev = NULL;
                }

                return head;
            }
        }
        else{

            table->nodes[index]=NULL;
            return head;
        }
        tail = head;
        head = head->next;
    }
    return NULL;
}