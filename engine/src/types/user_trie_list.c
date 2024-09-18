#ifndef NODE_LIST_C
#define NODE_LIST_C

#include <stdint.h>
#include <stdlib.h>
#include "./types.c"

bool hasChildren(struct TrieNode *node)
{
    if(node->childrens) return true;
    
    return false;
}

struct TrieList* createNode(struct TrieNode *node) 
{
    struct TrieList *l_node = calloc(1, sizeof(struct TrieList));
    l_node->node = node;
    l_node->next = NULL;
    return l_node;
}

struct TrieNode* insertNode(struct TrieList *root, struct TrieNode *node)
{
    struct TrieList *current = root;

    while(current) 
    {
        if(current->node->key == node->key) return current->node;

        if(!current->next) {
            current->next = createNode(node);
            break;
        }
        current = current->next;
    }

    return current->next->node;
}

struct TrieNode* getNode(struct TrieList *root, uint8_t key) 
{
    struct TrieList *current = root;
    while(current) 
    {
        if(current->node->key == key) return current->node;
        current = current->next;
    }
    return NULL;
}

void deleteNode(struct TrieList *root, uint8_t key)
{
    struct TrieList *current = root;
    struct TrieList *delete = root;
    while(current->next) 
    {
        if(current->next->node->key == key && !hasChildren(current->next->node)) 
        {
            delete = current->next;
            current->next = delete->next;
            free(delete->node);
            free(delete);
            return;
        }
        current = current->next;
    }
    if(root->node->key == key && !hasChildren(root->node)) {
        root = delete->next;
        free(delete->node);
        free(delete);
    }
}

void destroyNode(struct TrieList *root) 
{
    struct TrieList *delete;
    while(root->next) {
        delete = root->next;
        root->next = delete->next;
        free(delete->node);
        free(delete);
    }
    free(root->node);
    free(root);
}


#endif 
