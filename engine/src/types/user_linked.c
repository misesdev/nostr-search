#ifndef USER_LINKED_C
#define USER_LINKED_C

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./types.c"
#include "../utils/user_utils.c"

uint32_t indexOfUser(LinkedUsers *rootUsers, char *pubkey)
{
    for(uint32_t i = 0; i < rootUsers->count; i++)
        if(strcmp(rootUsers->users[i].pubkey, pubkey) == 0) return i;

    return -1;
}

User* insertUserLinked(LinkedUsers *rootUsers, User *user)
{
    if(rootUsers->count == rootUsers->size)
    {
        rootUsers->size += 100;
        rootUsers->users = realloc(rootUsers->users, rootUsers->size * sizeof(User));
    }

    User *insertUser = &rootUsers->users[rootUsers->count];

    copyUserData(user, insertUser);
    insertUser->index = rootUsers->count;
    insertUser->friends = user->friends;
    rootUsers->count++;

    return insertUser;
}

#endif


