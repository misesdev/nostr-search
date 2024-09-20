#ifndef WDISK_C
#define WDISK_C

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../utils/utils.c"
#include "../types/types.c"
#include "../types/user_list.c"
#include "../types/user_trie.c"
#include "./disk_utils.c"

void loadUserOnDisk(User *user, FILE *file, long offset) 
{
    fseek(file, offset, SEEK_SET);

    fwrite(user, sizeof(User), 1, file);
}

void loadUsersOnDisk(FILE *fileUsers, struct UserNode *rootUsers, long *userCount) 
{    
    long offset = 0;
    fseek(fileUsers, offset, SEEK_SET);
    fwrite(userCount, sizeof(long), 1, fileUsers);
    offset += sizeof(long);

    while (rootUsers) {
        if(rootUsers->user) {
            loadUserOnDisk(rootUsers->user, fileUsers, offset);
            offset += sizeof(User);
        }
        rootUsers = rootUsers->next;
    }
}

void serialiseUsersFromTrie(struct TrieNode *root, struct UserNode *rootUsers, long *userCount)
{
    struct TrieList *list = root->childrens;

    while(list) {
        if(list->node) {
            serialiseUsersFromTrie(list->node, rootUsers, userCount);
        }
        list = list->next;
    }

    if(root->isEndOfKey) {
        insertUserNode(rootUsers, root->user);
        *userCount += 1;
    }
}

void loadFriendsFromUser(FILE *file, User *user, long *offset)
{
    uint8_t address[ADDRESS_LENGTH] = {0};
    compressPubkey(user->pubkey, address);
    
    long friendsCount = 0;
    getFriendsCount(user->friends, &friendsCount);
    
    // write user address in tree
    fseek(file, *offset, SEEK_SET);    
    fwrite(&address, sizeof(uint8_t), ADDRESS_LENGTH, file);
    *offset += ADDRESS_LENGTH;
    
    // write user friends count
    fseek(file, *offset, SEEK_SET);
    fwrite(&friendsCount, sizeof(long), 1, file);
    *offset += sizeof(long);

    struct UserNode *current = user->friends;
    while (current) 
    {
        fseek(file, *offset, SEEK_SET);
        uint8_t friend[ADDRESS_LENGTH] = {0};
        compressPubkey(current->user->pubkey, friend);
        fwrite(&friend, sizeof(uint8_t), ADDRESS_LENGTH, file);
        *offset += ADDRESS_LENGTH;
        
        current = current->next;
    }
}

void loadFriendsOnDisk(FILE *file, struct UserNode *rootUsers, long *userCount)
{
    long offset = 0;
    // save the friend list count
    fseek(file, offset, SEEK_SET);
    fwrite(userCount, sizeof(long), 1, file);
    offset += sizeof(long);

    // save users list friends -> (address in the tree)
    struct UserNode *current = rootUsers;
    while (current) 
    {
        if(current->user) 
            loadFriendsFromUser(file, current->user, &offset);

        current = current->next;
    }
}

bool loadTrieInDisk(struct TrieNode *root) 
{
    mkdir("./data", 0777);

    FILE *fileUsers = fopen("./data/users.db", "wb");
    FILE *fileFriends = fopen("./data/friends.db", "wb");

    if(!fileUsers) return false;
    if(!fileFriends) return false;

    long userCount = 0;

    struct UserNode *rootUsers = createUserNode(NULL);

    serialiseUsersFromTrie(root, rootUsers, &userCount);

    loadUsersOnDisk(fileUsers, rootUsers, &userCount);

    loadFriendsOnDisk(fileFriends, rootUsers, &userCount);

    destroyUserNode(rootUsers);

    destroyTrieNode(root, false);

    fclose(fileFriends);
    fclose(fileUsers);

    return true;    
}

#endif


