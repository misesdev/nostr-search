#ifndef USERS_TRIE_C  
#define USERS_TRIE_C

#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include "./types.c"
#include "./trie_node_list.c"
#include "../utils/utils.c"

struct TrieNode* createTrieNode(uint8_t key) {
    struct TrieNode *node = malloc(sizeof(struct TrieNode));
    node->isEndOfKey = false;
    node->childrens = NULL;
    node->user = NULL;
    node->key = key;
    return node;
}

struct TrieNode* insertTrieNode(struct TrieNode *root, User *user)
{
    uint8_t address[ADDRESS_LENGTH];
    compressPubkey(user->pubkey, address);

    struct TrieList *current = root->childrens;

    for(uint8_t i = 0; i < ADDRESS_LENGTH; i++)
    {     
        if(!current) {
            current = createNode(createTrieNode(address[i]));
        }

        while(current->node->key != address[i]) {
            if(!current->next) break;
            current = current->next;
        }

        if(current->node->key != address[i]) {
            struct TrieNode *currentNode = insertNode(current, createTrieNode(address[i]));
            current = currentNode->childrens;
        }
    }

    current->node->isEndOfKey = true;
    current->node->user = user;

    return current->node;
}

bool deleteTrieNode(struct TrieNode *node, uint8_t *pubkey, uint8_t depth)
{
    if(!node) return false;
   
    if(depth == ADDRESS_LENGTH - 1) // if the end address 
    {
        if(node->isEndOfKey) node->isEndOfKey = false;

        if(!hasChildren(node)) {
            free(node->user);
            free(node);
            return true;
        }

        return false;
    }
    else {
        uint8_t index = pubkey[depth];
        if(deleteTrieNode(node, pubkey, depth+1)) {
            free(node->childrens[index]);
            node->children[index] = NULL;

            return !node->isEndOfKey && !hasChildren(node);
        }
    }
    return false;
}

void destroyTrieNode(struct TrieNode *root) {
    if(root == NULL) return;

    for(uint8_t i = 0; i < ADDRESS_LENGTH; i++) {
        if(node->children[i]) {
            destroyTrieNode(node->children[i]);
        }
    }
    if(!hasChildren(node)) {
        if(node->isEndOfKey) free(node->user);
        free(node);
    }
}

struct TrieNode* getTrieNode(struct TrieNode *root, uint8_t address[ADDRESS_LENGTH])
{
    struct TrieList* current = root->childrens;
   
    for(uint8_t i = 0; i < ADDRESS_LENGTH; i++) {
        while(current->node->key != address[i]) 
        {
            current = current->next;
        }
        if(current->node->key != address[i]) {
            current = current->node->childrens;
        } 
        else break;
    }

    if(current->node->isEndOfKey) 
        return current->node;

    return NULL;
}

struct TrieNode* getTrieNodeFromPubkey(struct TrieNode *root, char *pubkey)
{
    uint8_t address[ADDRESS_LENGTH];
    
    compressPubkey(pubkey, address);
    
    return getTrieNode(root, address);
}



#endif

