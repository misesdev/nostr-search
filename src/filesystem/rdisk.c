#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/user_trie.c"
#include "../types/friend_list.c"
#include "../types/user_list.c"

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

void loadFriends(struct TrieNode *root, User *user, FILE *file)
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

    struct UserNode *listFriends;

    while(friends) {
        User *friendUser = getTrieNode(root, friends->user)->user;
        
        insertUserNode(listFriends, friendUser);

        friends = friends->next;
    }

    user->friends = listFriends;
}

void loadFollowsTree(struct TrieNode *root, struct TrieNode *current, FILE *file)
{
    if(current == NULL) return;
   
    for(int i = 0; i < TRIE_CHILDREN_LENGTH; i++) {
        if(current->children[i]) {
            loadFollowsTree(root, current->children[i], file);
        }
    }
    
    if(current->isEndOfKey) {
        loadFriends(root, current->user, file); 
    }
}

struct TrieNode* loadFromDisk() 
{
    FILE *fileUsers = fopen("./data/users.db", "wb");
    FILE *fileFollows = fopen("./data/friends.db", "wb");

    if(!fileUsers) return NULL;
    if(!fileFollows) return NULL;

    struct TrieNode* root = createTrieNode();

    loadUsersTree(fileUsers, 0, false);
    
    loadFollowsTree(root, root, fileFollows);

    fclose(fileUsers);
    fclose(fileFollows);
    
    return root;
}


