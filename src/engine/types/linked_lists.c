#ifndef LINKED_LISTS_C
#define LINKED_LISTS_C

#include "../types/types.c"
#include <stdint.h>
#include <stdlib.h>

struct UserNode {
    User *user;
    struct UserNode *next;
};

struct UserNode* createUserNode(User *user)
{
    struct UserNode *node = malloc(sizeof(struct UserNode));

    node->user = user;

    return node;
}

#endif
