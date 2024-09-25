#ifndef RELAY_LIST_C
#define RELAY_LIST_C

#include <stdlib.h>
#include <string.h>

#include "../types/types.c"

struct RelayNode* createRelayNode(char *relay)
{
    struct RelayNode *node = malloc(sizeof(struct RelayNode));
    
    strcpy(node->address, relay);

    node->next = NULL;

    return node;
}

void insertRelayNode(struct RelayNode *root, char *relay)
{
    struct RelayNode *inserNode = createRelayNode(relay);

    struct RelayNode *current = root;

    while(current)
    {
        if(!current->next) {
            current->next = inserNode;
            return;
        }
        current = current->next;
    }
}

void destroyRelayNodes(struct RelayNode *node)
{
    struct RelayNode *delete;

    while(node->next) 
    {
        delete = node->next;
        node->next = delete->next;
        free(delete);
    }

    free(node);
}

long countRelayNodes(struct RelayNode *root)
{
    long count = 0;
    struct RelayNode *current = root;

    while(current)
    {
        count += 1;

        current = current->next;
    }

    return count;
}


#endif
