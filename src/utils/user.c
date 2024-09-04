#ifndef USER_UTILS_C
#define USER_UTILS_C

#include <stdlib.h>
#include <string.h>
#include "../types/types.c" 

User* createUser(char *name, char *pubkey, char *profile)
{
    User *user = malloc(sizeof(User));
    strcpy(user->profile, profile);
    strcpy(user->pubkey, pubkey);
    strcpy(user->name, name);
    user->friends = NULL;

    return user;
}

#endif  

