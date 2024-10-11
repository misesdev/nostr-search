#ifndef USER_LINKED_C
#define USER_LINKED_C

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./types.c"

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

    snprintf(insertUser->name, 45, "%s", user->name);
    snprintf(insertUser->pubkey, 65, "%s", user->pubkey);
    snprintf(insertUser->profile, 150, "%s", user->profile);
    snprintf(insertUser->displayName, 45, "%s", user->displayName);
    insertUser->index = rootUsers->count;
    insertUser->friends = NULL;
    rootUsers->count++;

    free(user);

    return insertUser;
}

#endif


