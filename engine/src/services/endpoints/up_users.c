#ifndef UP_USERS_C
#define UP_USERS_C

#include "../../types/types.c"
#include "../../utils/user_utils.c"
#include "../../types/user_trie.c"

#include <stdio.h>
#include <unistd.h>

HttpResponse* insertUser(char *jsonRequest, HttpResponse *response, struct TrieNode *root)
{
    User *user = getUserFromRequest(jsonRequest, response->Content);
    
    if(!user) {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = insertTrieNode(root, user);

    printf("user inserted: %s\n", userNode->user->displayName);

    responseMessage(response->Content, "User added successfully");
    response->StatusCode = 200;

    return response;
}


#endif


