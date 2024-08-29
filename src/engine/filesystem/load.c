#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/user_trie.c"

struct TrieNode* loadUsersTree(FILE *file, long offset, struct TrieNode *root) 
{    
    fseek(file, offset, SEEK_SET);

    struct TrieNode *diskNode = malloc(sizeof(struct TrieNode));

    fread(&diskNode, sizeof(struct TrieNode), 1, file);
    
    for(int i = 0;i < 200; i++) {
        if(diskNode->children[i]) {
            offset += sizeof(struct TrieNode);
            root->children[i] = loadUsersTree(file, offset, root);
        }
    }

    return root;
}

void loadFollows(struct TrieNode *root, FILE *file)
{
    long offset = 0;

    while(fseek(file, offset, SEEK_SET)) 
    {
        
        offset += sizeof(uint8_t) * 16;
    }
}

struct TrieNode* loadFromDisk() 
{
    FILE *fileUsers = fopen("./data/users.nd", "wb");
    FILE *fileFollows = fopen("./data/folows.nd", "wb");

    if(!fileUsers) return NULL;
    if(!fileFollows) return NULL;

    struct TrieNode* root = createTrieNode();

    loadUsersTree(fileUsers, 0, false);
    
    loadFollows(root, fileFollows);

    fclose(fileUsers);
    fclose(fileFollows);
    
    return root;
}


void loadInDisk(struct TrieNode *root) 
{

}

