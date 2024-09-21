#ifndef R_DISK_C
#define R_DISK_C

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../types/types.c"
#include "../types/user_trie.c"
#include "../utils/user_utils.c"

User* loadUserFromDisk(FILE *file, long offset) 
{
    fseek(file, offset, SEEK_SET);

    User *user = calloc(1, sizeof(User));

    fread(user, sizeof(User), 1, file);

    user->friends = NULL;

    return user;
}

struct TrieNode* loadUsersTree(FILE *file) 
{
    long count = 0, offset = 0;
    fseek(file, offset, SEEK_SET);
    fread(&count, sizeof(long), 1, file);
    offset += sizeof(long);

    printf("users count: %ld\n", count);

    struct TrieNode *root = createTrieNode(0);

    for(int i = 0; i < count; i++) 
    {
        User *currentUser = loadUserFromDisk(file, offset);
        insertTrieNode(root, currentUser);
        offset += sizeof(User);
    }

    return root;
}

void loadFriendsOnTree(FILE *file, struct TrieNode *root, long *offset)
{
    uint8_t address[ADDRESS_LENGTH];

    fseek(file, *offset, SEEK_SET);
    fread(&address, sizeof(uint8_t), ADDRESS_LENGTH, file);
    *offset += ADDRESS_LENGTH;

    struct TrieNode *userNode = getTrieNode(root, address);

    if(userNode) 
    {
        long friendsCount = 0;
        fseek(file, *offset, SEEK_SET);
        fread(&friendsCount, sizeof(long), 1, file);
        *offset += sizeof(long);

        uint8_t friends[friendsCount][ADDRESS_LENGTH];

        fseek(file, *offset, SEEK_SET);
        fread(&friends, ADDRESS_LENGTH, friendsCount, file);
        *offset += ADDRESS_LENGTH * friendsCount;

        for(long i = 0; i < friendsCount; i++) 
        {
            uint8_t friend[ADDRESS_LENGTH];

            for(uint8_t j = 0; j < ADDRESS_LENGTH; j++)
                friend[j] = friends[i][j];
            
            struct TrieNode *friendNode = getTrieNode(root, friend);
            
            if(friendNode->user) 
                insertFriend(userNode->user, friendNode->user);            
        }
    }
}

void loadFriendsFromDisk(FILE *file, struct TrieNode *root)
{
    long usersCount = 0, offset = 0;
    fseek(file, offset, SEEK_SET);
    fread(&usersCount, sizeof(long), 1, file);
    offset += sizeof(long);

    for(long i = 0; i < usersCount; i++) {
        loadFriendsOnTree(file, root, &offset);
    }
}

struct TrieNode* loadTrieFromDisk() 
{
    mkdir("./data", 0777);

    long defaultUsers = 0, offset = 0;

    FILE *fileUsers = fopen("./data/users.db", "rb");
    FILE *fileFriends = fopen("./data/friends.db", "rb");

    if(!fileUsers) 
    {
        FILE *file = fopen("./data/users.db", "wb");
        
        if(!file) return NULL;

        fseek(file, offset, SEEK_SET);
        fwrite(&defaultUsers, sizeof(long), 1, file);
        fclose(file);

        fileUsers = fopen("./data/users.db", "rb");

        if(!fileUsers) return NULL;
    }

    if(!fileFriends) 
    {
        FILE *file = fopen("./data/friends.db", "wb");
        
        if(!file) return NULL;

        fseek(file, offset, SEEK_SET);
        fwrite(&defaultUsers, sizeof(long), 1, file);
        fclose(file);

        fileFriends = fopen("./data/friends.db", "rb");

        if(!fileFriends) return NULL;
    }

    struct TrieNode* root = loadUsersTree(fileUsers);
    
    loadFriendsFromDisk(fileFriends, root);

    fclose(fileFriends);
    fclose(fileUsers);
    
    return root;
}

#endif
