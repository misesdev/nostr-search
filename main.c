#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./src/types/user_list.c"
#include "./src/utils/http_utils.c"
#include "./src/types/user_trie.c"
#include "./src/filesystem/wdisk.c"
#include "./src/filesystem/rdisk.c"
#include "./src/utils/utils.c"

char* requestProssess(char *request) 
{
    // get the parameter from request
    Search *params = requestParams(request);
    // Search for terms and more
    User *user;
    strcpy(user->name, "Mises Dev");
    strcpy(user->profile, "");
    strcpy(user->pubkey, "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93");

    struct UserNode *list = createUserNode(user);
    
    return jsonResult(list);
}

int main(int argc, char *args[]) 
{
    char *pubkey = "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93";
    User *user = malloc(sizeof(User));
    strcpy(user->name, "Mises Dev");
    strcpy(user->pubkey, pubkey);

    struct TrieNode *root = createTrieNode(); 

    insertTrieNode(root, user);
    
    if(!loadTrieInDisk(root)) {
        printf("Error when trying to load the tree to disk");
        return -1;
    }

    struct TrieNode *t_root = loadTrieFromDisk();

    if(!t_root) {
        printf("Error when trying to load the disk tree");
        return -1;
    }

    uint8_t address[16];
    compressPubkey(pubkey, address);

    struct TrieNode *t_node = getTrieNode(t_root, address);

    if(t_node) {
        printf("Found user: %s", t_node->user->name);
    }
    //serverUp(&requestProssess);

    //clearTrieNode(node);
    return 0;
}


