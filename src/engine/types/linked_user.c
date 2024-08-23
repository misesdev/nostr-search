#include "../types/types.c"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct UserNode {
    User * user;
    struct UserNode *previous;
    struct UserNode *next;
};

struct UserNode* createUserNode(User *user)
{
    struct UserNode *node = malloc(sizeof(struct UserNode));

    strcpy(node->user->name, user->name);
    
    for(uint8_t i = 0; i < sizeof(user->npub); i++) {
        node->user->npub[i] = user->npub[i];
    }

    return node;
}


