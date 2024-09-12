#ifndef USER_UTILS_C
#define USER_UTILS_C

#include <stdint.h>
#include <stdio.h>
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

void showUsersOfTrie(struct TrieNode *root)
{
    struct TrieList *list = root->childrens;

    while(list) {
        showUsersOfTrie(list->node);
        list = list->next;
    }

    if(root->isEndOfKey) {
        printf("username: %s\n", root->user->name);
        printf("    pubkey: %s\n", root->user->pubkey);
        struct UserNode *friends = root->user->friends;
        while(friends) {
            printf("    friend: %s\n", friends->user->name);
            friends = friends->next;
        }
    }
}
//void compressPubkey(char *pubkey, uint8_t *address)

#endif  

