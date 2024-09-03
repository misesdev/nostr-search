#ifndef WDISK_C
#define WDISK_C

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "../utils/utils.c"
#include "../types/types.c"
#include "../types/user_list.c"

long usersOffset = 0;

void loadUserOnDisk(User *user, FILE *file) 
{
    fseek(file, usersOffset, SEEK_SET);

    fwrite(user, sizeof(User), 1, file);

    usersOffset += sizeof(User);
}

bool loadTrieUsersOnDisk(FILE *fileTrie, FILE *fileUsers, long offset, struct TrieNode *root, struct UserNode *userList) 
{
    fseek(fileTrie, offset, SEEK_SET);

    fwrite(root, sizeof(struct TrieNode), 1, fileTrie);
    
    for(int i = 0; i < TRIE_CHILDREN_LENGTH; i++) {
        if(root->children[i]) {
            offset += sizeof(struct TrieNode);
            loadTrieUsersOnDisk(fileTrie, fileUsers, offset, root->children[i], userList);
        }
    }

    if(root->isEndOfKey) {
        loadUserOnDisk(root->user, fileUsers);
        insertUserNode(userList, root->user);
    }

    return true;
}

int friendsOffset = 0;

void loadFriendsFromUser(uint8_t *user, struct UserNode *friends, FILE *file)
{
    int userCount = 0;
    struct UserNode *current = friends;
    fseek(file, friendsOffset, SEEK_SET);

    while(current) {
        userCount++;
        current = current->next;
    }

    // write user address in tree
    fwrite(&userCount, sizeof(int), 1, file);
    friendsOffset += sizeof(int);

    current = friends;
    uint8_t address[PUBKEY_ADDRESS_LENGTH];
    while (current) {
        fseek(file, friendsOffset, SEEK_SET);
        compressPubkey(current->user->pubkey, address);
        fwrite(&address, sizeof(uint8_t), PUBKEY_ADDRESS_LENGTH, file);
        friendsOffset += PUBKEY_ADDRESS_LENGTH;
        current = current->next;
    }
}

void loadFriendsOnDisk(struct UserNode *userList, FILE *file)
{
    int userCount = 0;
    struct UserNode *current = userList->next;
    
    while(current) {
        current = current->next;
        userCount++;
    }

    // save the friend list count
    fseek(file, friendsOffset, SEEK_SET);
    fwrite(&userCount, sizeof(int), 1, file);
    friendsOffset += sizeof(int);

    current = userList->next;
    uint8_t user[PUBKEY_ADDRESS_LENGTH];
    while (current) {
        compressPubkey(current->user->pubkey, user);
        loadFriendsFromUser(user, current->user->friends, file);
        current = current->next;
    }
}

bool loadTrieInDisk(struct TrieNode *root) 
{
    if(mkdir("./data", 0777) == -1) {
        printf("Failed to create directory of data");
        return false;
    }

    FILE *fileTrie = fopen("./data/trie.db", "wb");
    FILE *fileUsers = fopen("./data/users.db", "wb");
    FILE *fileFriends = fopen("./data/friends.db", "wb");

    if(!fileTrie) return false;
    if(!fileUsers) return false;
    if(!fileFriends) return false;

    struct UserNode *userList = malloc(sizeof(User));
    
    loadTrieUsersOnDisk(fileTrie, fileUsers, 0, root, userList);

    loadFriendsOnDisk(userList, fileFriends);

    fclose(fileFriends);
    fclose(fileUsers);
    fclose(fileTrie);

    return true;    
}

#endif


