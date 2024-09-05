#ifndef FRIEND_LICT_C
#define FRIEND_LICT_C

#include <stdint.h>
#include <stdlib.h>
#include "./types.c"

int compareUserAddresses(uint8_t first[PUBKEY_ADDRESS_LENGTH], uint8_t second[PUBKEY_ADDRESS_LENGTH])
{
    uint8_t map[TRIE_CHILDREN_LENGTH] = {0};
    uint8_t interssections = 0;
    for(int i = 0; i < PUBKEY_ADDRESS_LENGTH; i++){
        map[first[i]]++;
    }
    for(int i = 0; i < PUBKEY_ADDRESS_LENGTH; i++){
        map[second[i]]++;
    }
    for(int i = 0; i < TRIE_CHILDREN_LENGTH; i++) {
        if(map[i] > 1) interssections++;
    }
    
    return (interssections > PUBKEY_ADDRESS_LENGTH - 1);
}

struct FriendNode* createFriendNode(uint8_t user[PUBKEY_ADDRESS_LENGTH])
{
    struct FriendNode *node = malloc(sizeof(struct FriendNode));
    for(int i = 0; i < PUBKEY_ADDRESS_LENGTH; i++) {
        node->user[i] = user[i];
    }

    return node;
}

void insertFriendNode(struct FriendNode *root, uint8_t friend[PUBKEY_ADDRESS_LENGTH]) 
{
    while(1) {
        if(!root->next) {
            root->next = createFriendNode(friend);
        }
        root = root->next;
    }
}

struct FriendNode* getFriendNode(struct FriendNode *root, uint8_t friend[PUBKEY_ADDRESS_LENGTH])
{
    struct FriendNode *current = root;
    while (current) {
        if(compareUserAddresses(current->user, friend)) return current;
        current = current->next;
    }

    return NULL;
}

void deleteFriendNode(struct FriendNode *root, uint8_t friend[PUBKEY_ADDRESS_LENGTH])
{
    struct FriendNode *current = root;
    struct FriendNode *delete;
    while (current) {
        if(compareUserAddresses(current->user, friend)) {
            delete = current;
            current = current->next;
            free(delete);
        }
        current = current->next;
    }
}

void destroyFriendNodeList(struct FriendNode *root)
{
    struct FriendNode *delete;

    while(root->next) {
        delete = root->next;
        root->next = delete->next;
        free(delete);
    }

    free(root);
}

#endif
