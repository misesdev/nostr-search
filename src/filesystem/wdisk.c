#ifndef WDISK_C
#define WDISK_C

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"
#include "../types/user_trie.c"
#include "../types/friend_list.c"
#include "../types/user_list.c"

void loadFriendsOnDisk() 
{

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

    if(root->isEndOfKey) {

    }

    return 0;
}

int loadInDisk(struct TrieNode *root) 
{
    FILE *fileTrie = fopen("./data/trie.db", "wb");
    FILE *fileUsers = fopen("./data/users.db", "wb");
    FILE *fileFriends = fopen("./data/folows.db", "wb");

    if(!fileTrie) return -1;
    if(!fileUsers) return -1;
    if(!fileFriends) return -1;

    loadTrieOnDisk(fileTrie, 0, root);

    return 0;    
}

#endif
