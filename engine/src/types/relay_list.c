#ifndef RELAY_LIST_C
#define RELAY_LIST_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constants/index.c"
#include "../types/types.c"
#include "../utils/utils.c"

struct RelayNode* createRelayNode(char *relay)
{
    struct RelayNode *node = malloc(sizeof(struct RelayNode));
    
    snprintf(node->address, RELAY_SIZE, "%s", relay);

    node->next = NULL;

    return node;
}

void insertRelayNode(struct RelayNode *root, char *relay)
{
    if(strlen(root->address) <= 0) {
        snprintf(root->address, RELAY_SIZE, "%s", relay);
        return;
    }
   
    struct RelayNode *current = root;
    while(current)
    {
        if(textSimilarity(current->address, relay) >= .90) return;

        if(!current->next) {
            current->next = createRelayNode(relay);
            return;
        }
        current = current->next;
    }
}

void destroyRelayNode(struct RelayNode *node)
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
