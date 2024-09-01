#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "./src/utils/http_utils.c"
#include "./src/types/user_trie.c"
#include "./src/utils/http_utils.c"
#include "./src/server.c"

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
    User *user = malloc(sizeof(User));
    strcpy(user->name, "Mises Dev");
    strcpy(user->pubkey, "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93");

    struct TrieNode *node = createTrieNode(); 

    insertTrieNode(node, user, NULL);

    //deleteTrieNode(node, compressPubkey(user->pubkey), 0);

    struct TrieNode *unode = getTrieNode(node, "6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93");
    printf("username: %s\n", unode->user->name);

    serverUp(&requestProssess);

    //clearTrieNode(node);
    return 0;
}


