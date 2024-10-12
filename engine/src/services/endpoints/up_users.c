#ifndef UP_USERS_C
#define UP_USERS_C

#include <stdio.h>
#include <unistd.h>

#include "../../types/types.c"
#include "../../types/user_linked.c"
#include "../../utils/user_utils.c"
#include "../../types/user_trie.c"

HttpResponse* insertUser(char *jsonRequest, HttpResponse *response, Database *root)
{
    User *user = jsonToUser(jsonRequest, response->Content);
    
    if(!user) {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userExists = getTrieNodeFromPubkey(root->tree, user->pubkey);

    if(userExists) 
    {
        insertTrieNode(root->tree, user);

        responseMessage(response->Content, "User added successfully");
        response->StatusCode = 200;
        free(user);
        return response;
    }

    User *insertUser = insertUserLinked(root->users, user);

    struct TrieNode *userNode = insertTrieNode(root->tree, insertUser);

    printf("user inserted: %s\n", userNode->user->displayName);

    responseMessage(response->Content, "User added successfully");

    response->StatusCode = 200;

    return response;
}


#endif


