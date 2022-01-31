#define CLOVE_SUITE_NAME sets_test
// #include "..\include\clove-experimental.h"
#include "clove-experimental.h"
#include "my_sets.h"

set_table_t *table=NULL;

CLOVE_SUITE_SETUP()
{
    table = set_table_new(3);
}

CLOVE_TEST(Insert_One_Element){
    set_node_t *node = set_insert(table,"ciao",4);
    CLOVE_NOT_NULL(node);
}

CLOVE_TEST(Insert_Two_Element){
    set_node_t *node = set_insert(table,"ciao",4);
    set_node_t *node1 = set_insert(table,"ciao0",5);
    CLOVE_NOT_NULL(node);
    CLOVE_NOT_NULL(node1);
}
CLOVE_TEST(Insert_Same_Key){

    set_node_t *node = set_insert(table,"ciao",4);
    set_node_t *node2 = set_insert(table,"ciao",4);

    CLOVE_NULL(node2);
}

CLOVE_TEST(Search_Value){
    set_node_t *node = set_insert(table,"ciao",4);
    set_node_t *node2 = set_insert(table,"ciao0",5);

    CLOVE_PTR_EQ(node,set_table_search(table,"ciao",4));
}

CLOVE_TEST(Remove_Item){
    set_node_t *node = set_insert(table,"ciao",4);
    set_node_t *node2 = set_insert(table,"ciao0",5);
    
    set_node_t *node_removed = set_table_remove(table,"ciao",4);
    CLOVE_PTR_EQ(node,node_removed);
    }
