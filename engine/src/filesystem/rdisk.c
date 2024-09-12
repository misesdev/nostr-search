#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/user_trie.c"
#include "../types/friend_list.c"
#include "../types/user_list.c"
#include "../utils/user_utils.c"

User* loadUserFromDisk(FILE *file, long offset) 
{
    fseek(file, offset, SEEK_SET);

    User *user = malloc(sizeof(User));

    fread(user, sizeof(User), 1, file);

    user->friends = NULL;

    return user;
}

struct TrieNode* loadUsersTree(FILE *file, long *usersCount) 
{
    User *currentUser;
    long count, offset = 0;

    fseek(file, offset, SEEK_SET);
    fread(&count, sizeof(long), 1, file);
    offset += sizeof(long);

    struct TrieNode *root = createTrieNode(0);

    for(int i = 0; i < count; i++) {
        currentUser = loadUserFromDisk(file, offset);
        insertTrieNode(root, currentUser);
        offset += sizeof(User);
        usersCount++;
    }

    return root;
}

void loadFriendOnTree(FILE *file, struct TrieNode *root, long *offset)
{
    uint8_t address[ADDRESS_LENGTH];

    fseek(file, *offset, SEEK_SET);
    fread(&address, sizeof(uint8_t), ADDRESS_LENGTH, file);
    *offset += ADDRESS_LENGTH;

    for (int i = 0; i < ADDRESS_LENGTH; i++)
        printf("%d ", address[i]);
    printf("\n");

    struct TrieNode *userNode = getTrieNode(root, address);

    if(userNode->user) 
    {
        // long friendscount;
        // fseek(file, *offset, SEEK_SET);
        // fread(&friendscount, sizeof(long), 1, file);
        // *offset += sizeof(long);

        // for(long i = 0; i < friendscount; i++) 
        // {
        //     fseek(file, *offset, SEEK_SET);
        //     fread(&address, sizeof(uint8_t), ADDRESS_LENGTH, file);
        //     *offset += ADDRESS_LENGTH;

        //     struct TrieNode *friendNode = getTrieNode(root, address);
        //     
        //     if(friendNode->user) {
        //         insertFriend(userNode->user, friendNode->user);
        //     }
        // }
    }
}

void loadFriendsFromDisk(FILE *file, struct TrieNode *root)
{
    long offset = 0;
    long usersCount;
    fseek(file, offset, SEEK_SET);
    fread(&usersCount, sizeof(long), 1, file);
    offset += sizeof(long);
    printf("users: %ld\n", usersCount);

    for(long i = 0; i < usersCount; i++) {
        loadFriendOnTree(file, root, &offset);
    }
}

struct TrieNode* loadTrieFromDisk() 
{
    FILE *fileUsers = fopen("./data/users.db", "rb");
    FILE *fileFriends = fopen("./data/friends.db", "rb");

    if(!fileUsers) return NULL;
    if(!fileFriends) return NULL;

    long usersCount = 0;
    struct TrieNode* root = loadUsersTree(fileUsers, &usersCount);
    
    loadFriendsFromDisk(fileFriends, root);

    fclose(fileUsers);
    fclose(fileFriends);
    
    return root;
}

