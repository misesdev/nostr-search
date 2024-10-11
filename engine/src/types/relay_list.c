#ifndef RELAY_LIST_C
#define RELAY_LIST_C

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../constants/index.c"
#include "../types/types.c"
#include "../utils/string_utils.c"

struct RelayNode* createRelayNode(char *relay, float similarity)
{
    struct RelayNode *node = malloc(sizeof(struct RelayNode));
    
    snprintf(node->address, RELAY_SIZE, "%s", relay);

    node->similarity = similarity;

    node->next = NULL;

    return node;
}

void insertRelayNode(struct RelayNode *root, char *relay, float similarity)
{
    if(strlen(root->address) <= 0) {
        snprintf(root->address, RELAY_SIZE, "%s", relay);
        root->similarity = similarity;
        return;
    }
   
    struct RelayNode *current = root;
    while(current)
    {
        if(textSimilarity(current->address, relay) >= .90) return;

        if(!current->next) {
            current->next = createRelayNode(relay, similarity);
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

uint32_t countRelayNodes(struct RelayNode *root)
{
    uint32_t count = 0;
    struct RelayNode *current = root;

    while(current)
    {
        count += 1;

        current = current->next;
    }

    return count;
}


#endif
