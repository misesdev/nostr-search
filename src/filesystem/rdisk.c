#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/user_trie.c"
#include "../types/friend_list.c"

struct TrieNode* loadUsersTree(FILE *file, long offset, struct TrieNode *root) 
{    
    fseek(file, offset, SEEK_SET);

    struct TrieNode *diskNode = malloc(sizeof(struct TrieNode));

    fread(&diskNode, sizeof(struct TrieNode), 1, file);
    
    for(int i = 0;i < TRIE_CHILDREN_LENGTH; i++) {
        if(diskNode->children[i]) {
            offset += sizeof(struct TrieNode);
            root->children[i] = loadUsersTree(file, offset, root);
        }
    }

    return root;
}

long offsetFriends = 0;

void loadFriends(User *user, FILE *file)
{
    fseek(file, offsetFriends, SEEK_SET);

    struct FriendNode *friends = malloc(sizeof(struct FriendNode));

    fread(&(friends->user), PUBKEY_ADDRESS_LENGTH * sizeof(uint8_t), 1, file);

    offsetFriends += sizeof(FriendList);

    struct FriendNode *current = friends;

    while (fseek(file, offsetFriends, SEEK_SET)) 
    { 
        uint8_t *address[PUBKEY_ADDRESS_LENGTH];

        fread(address, PUBKEY_ADDRESS_LENGTH * sizeof(uint8_t), 1, file);

        offsetFriends += (PUBKEY_ADDRESS_LENGTH * sizeof(uint8_t)); 

        if(isEmptyAddress((*address))) break;

        current->next = createFriendNode((*address)); 
        current = current->next;
    }

    //user->friends = friends;
}

void loadFollowsTree(struct TrieNode *root, FILE *file)
{
    if(root == NULL) return;
   
    for(int i = 0; i < TRIE_CHILDREN_LENGTH; i++) {
        if(root->children[i]) {
            loadFollowsTree(root->children[i], file);
        }
    }
    
    if(root->isEndOfKey) {
        loadFriends(root->user, file); 
    }
}

struct TrieNode* loadFromDisk() 
{
    FILE *fileUsers = fopen("./data/users.nd", "wb");
    FILE *fileFollows = fopen("./data/friends.nd", "wb");

    if(!fileUsers) return NULL;
    if(!fileFollows) return NULL;

    struct TrieNode* root = createTrieNode();

    loadUsersTree(fileUsers, 0, false);
    
    loadFollowsTree(root, fileFollows);

    fclose(fileUsers);
    fclose(fileFollows);
    
    return root;
}

int loadTrieOnDisk(FILE *file, long offset, struct TrieNode *root) 
{
    fseek(file, offset, SEEK_SET);

    fwrite(root, sizeof(struct TrieNode), 1, file);
    
    for(int i = 0; i < TRIE_CHILDREN_LENGTH; i++) {
        if(root->children[i]) {
            offset += sizeof(struct TrieNode);
            loadTrieOnDisk(file, offset, root->children[i]);
        }
    }

    return 0;
}

int loadFollowsOnDisk(FILE *file, long offset) 
{

    return 0;
}

int loadInDisk(struct TrieNode *root) 
{
    FILE *fileUsers = fopen("./data/users.nd", "wb");
    FILE *fileFollows = fopen("./data/folows.nd", "wb");

    if(!fileUsers) return -1;
    if(!fileFollows) return -1;

    return 0;    
}

