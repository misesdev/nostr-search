#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/user_trie.c"
#include "../types/friend_list.c"
#include "../types/user_list.c"

long userOffset = 0;

User* loadUserFromDisk(FILE *file, long offset) 
{
    fseek(file, offset, SEEK_SET);

    User *user = malloc(sizeof(User));

    fread(&user, sizeof(User), 1, file);

    return user;
}

struct TrieNode* loadUsersTree(FILE *fileTrie, FILE *fileUsers, long offset, struct TrieNode *root) 
{    
    fseek(fileTrie, offset, SEEK_SET);

    struct TrieNode *diskNode = malloc(sizeof(struct TrieNode));

    fread(&diskNode, sizeof(struct TrieNode), 1, fileTrie);
    
    for(int i = 0;i < TRIE_CHILDREN_LENGTH; i++) {
        if(diskNode->children[i]) {
            offset += sizeof(struct TrieNode);
            root->children[i] = loadUsersTree(fileTrie, fileUsers, offset, diskNode->children[i]);
        }
    }

    // load user for address
    if(diskNode->isEndOfKey) {
        diskNode->user = loadUserFromDisk(fileUsers, userOffset);
        userOffset += sizeof(User);
    }

    return root;
}

long friendOffset = 0;

void loadFriendList(FILE *file, FriendList *friends)
{
    fseek(file, friendOffset, SEEK_SET);
    fread(friends->user, sizeof(uint8_t), PUBKEY_ADDRESS_LENGTH, file);
    friendOffset += PUBKEY_ADDRESS_LENGTH;

    int friendsCount;
    fseek(file, friendOffset, SEEK_SET);
    fread(&friendsCount, sizeof(int), 1, file);
    friendOffset += sizeof(int);

    struct FriendNode *current = friends->friends; 

    uint8_t user[PUBKEY_ADDRESS_LENGTH];
    for(int i = 0; i < friendsCount; i++) {
        fseek(file, friendOffset, SEEK_SET);
        fread(&user, sizeof(uint8_t), PUBKEY_ADDRESS_LENGTH, file);
        friendOffset += PUBKEY_ADDRESS_LENGTH;
        current = createFriendNode(user);
        current = current->next;
    }
}

FriendList* loadFriendListFromDisk(FILE *file, int *count)
{
    fread(&count, sizeof(int), 1, file);
    friendOffset += sizeof(int);

    FriendList *friends = malloc(*count * sizeof(FriendList));

    for(int i = 0; i < *count; i++) {
        loadFriendList(file, &friends[i]);
    }
    
    return friends;
}

void serializeFriendsOnTrie(struct TrieNode *root, FriendList *friends, int friendsCount)
{
    User *currentUser;
    User *currentFriendUser;
    struct FriendNode *currentFriend;

    for(int i = 0; i < friendsCount; i++) {
        currentFriend = friends[i].friends;
        currentUser = getTrieNode(root, friends->user)->user;

        while (currentFriend) {  
            currentFriendUser = getTrieNode(root, currentFriend->user)->user;

            insertUserNode(currentUser->friends, currentUser);

            currentFriend = currentFriend->next;
        }

        destroyFriendNodeList(friends[i].friends);
        free(&friends[i]);
    }
}

struct TrieNode* loadTrieFromDisk() 
{
    FILE *fileTrie = fopen("./data/trie.db", "rb");
    FILE *fileUsers = fopen("./data/users.db", "rb");
    FILE *fileFriends = fopen("./data/friends.db", "rb");

    if(!fileTrie) return NULL;
    if(!fileUsers) return NULL;
    if(!fileFriends) return NULL;

    struct TrieNode* root = createTrieNode();

    loadUsersTree(fileTrie, fileUsers, 0, root);
    
    int friendsCount;
    FriendList *friends = loadFriendListFromDisk(fileFriends, &friendsCount);

    serializeFriendsOnTrie(root, friends, friendsCount);

    fclose(fileTrie);
    fclose(fileUsers);
    fclose(fileFriends);
    
    return root;
}

