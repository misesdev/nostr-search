#ifndef WDISK_C
#define WDISK_C

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../utils/utils.c"
#include "../types/types.c"
#include "../types/user_list.c"

void loadUserOnDisk(User *user, FILE *file, long offset) 
{
    fseek(file, offset, SEEK_SET);

    fwrite(user, sizeof(User), 1, file);
}

void loadUsersOnDisk(FILE *fileUsers, struct UserNode *rootUsers, long userCount) 
{    
    long offset = 0;
    fseek(fileUsers, offset, SEEK_SET);
    fwrite(&userCount, sizeof(long), 1, fileUsers);
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
        serialiseUsersFromTrie(list->node, rootUsers, userCount);
        list = list->next;
    }

    if(root->isEndOfKey) {
        insertUserNode(rootUsers, root->user);
        *userCount += 1;
    }
}

void loadFriendsFromUser(FILE *file, struct UserNode *friends, uint8_t user[ADDRESS_LENGTH], long *offset)
{
    long friendsCount = 0;
    struct UserNode *current = friends;
    fseek(file, *offset, SEEK_SET);

    while(current) {
        if(current->user) friendsCount++;
        current = current->next;
    }

    // write user address in tree
    fwrite(&user, sizeof(uint8_t), ADDRESS_LENGTH, file);
    *offset += ADDRESS_LENGTH;
    
    // write user friends count
    fwrite(&friendsCount, sizeof(int), 1, file);
    offset += sizeof(int);

    current = friends;
    uint8_t address[ADDRESS_LENGTH];
    while (current) {
        if(current->user) {
            fseek(file, *offset, SEEK_SET);
            compressPubkey(current->user->pubkey, address);
            fwrite(&address, sizeof(uint8_t), ADDRESS_LENGTH, file);
            *offset += ADDRESS_LENGTH;
        }
        current = current->next;
    }
}

void loadFriendsOnDisk(struct UserNode *usersRoot, FILE *file, long userCount)
{
    long offset = 0;
    // save the friend list count
    fseek(file, offset, SEEK_SET);
    fwrite(&userCount, sizeof(int), 1, file);
    offset += sizeof(int);

    // save users list friends -> (address in the tree)
    uint8_t address[ADDRESS_LENGTH];
    struct UserNode *current = usersRoot;
    while (current) {
        if(current->user) {
            compressPubkey(current->user->pubkey, address);
            loadFriendsFromUser(file, current->user->friends, address, &offset);
        }
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
    
    loadUsersOnDisk(fileUsers, rootUsers, userCount);

    loadFriendsOnDisk(rootUsers, fileFriends, userCount);

    //destroyUserNode(rootUsers);

    fclose(fileFriends);
    fclose(fileUsers);

    return true;    
}

#endif


