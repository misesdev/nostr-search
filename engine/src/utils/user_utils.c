#ifndef USER_UTILS_C
#define USER_UTILS_C

#include <stdlib.h>
#include <string.h>
#include "../types/types.c" 
#include "../types/user_list.c"

User* createUser(char *name, char *profile, char *pubkey)
{
    User *user = malloc(sizeof(User));
    strcpy(user->profile, profile);
    strcpy(user->pubkey, pubkey);
    strcpy(user->name, name);
    user->friends = NULL;

    return user;
}

void insertFriend(User *user, User *friend)
{
    if(!user->friends) {
        user->friends = createUserNode(friend);
        return;
    }

    struct UserNode *current = user->friends;
    while(current) {
        if(!current->next) {
            current->next = createUserNode(friend);
            break;
        }
        current = current->next;
    }
}

#endif  

