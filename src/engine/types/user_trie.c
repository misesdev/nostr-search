#ifndef USERS_TRIE_C  
#define USERS_TRIE_C

#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include "./types.c"
#include "../utils/utils.c"

uint8_t* compressPubkey(char *pubkey)
{
    uint8_t index = 0;
    uint8_t *address = malloc(16 * sizeof(uint8_t));
    uint8_t *numbers = hexToBytes(pubkey);

    for(uint8_t i = 0; i < 32; i += 2) {
        address[index] = (numbers[i] * numbers[i+1]) % 255;
        index++;
    }
    free(numbers);

    return address;
}

struct TrieNode* createTrieNode() {
    struct TrieNode *node = malloc(sizeof(struct TrieNode));
    
    return node;
}

void insertTrieNode(struct TrieNode *node, User *user, struct UserNode *follows)
{
    struct TrieNode* t_node = node;
    uint8_t *address = compressPubkey(user->pubkey);

    for(uint8_t i = 0; i < 16; i++){
        t_node->nodes[address[i]] = createTrieNode();
        t_node = t_node->nodes[address[i]];
    }

    t_node->user = user;
    t_node->follows = follows;

    free(address);
}

void deleteTrieNode(User *user)
{
    
}

void clearTrieNode(struct TrieNode *node) {

}

struct TrieNode* getUserTrieNode(struct TrieNode *node, char *pubkey)
{
    struct TrieNode* t_node = node;
    uint8_t *address = compressPubkey(pubkey);
    
    for(uint8_t i = 0; i < 16; i++){
        if(t_node->nodes[address[i]]) {
            t_node = t_node->nodes[address[i]];
        } else {
            return NULL;
        }
    }

    return t_node;
}


#endif 
