#ifndef GET_FRIENDS_C
#define GET_FRIENDS_C

#include <stdlib.h>
#include "../../types/types.c" 
#include "../../types/user_trie.c"
#include "../../utils/user_utils.c"

HttpResponse* getFriendsFromUser(char *jsonRequest, HttpResponse *response, Database *root)
{
    UserIdentity *identity = jsonToIdentity(jsonRequest, response->Content);

    if(!identity) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNodeFromPubkey(root->tree, identity->pubkey);

    free(identity);

    if(!userNode) 
    {
        responseMessage(response->Content, "Focal user not found, please provide a existent public key");
        response->StatusCode = 403;
        return response;
    }

    userListToJson(userNode->user->friends, response->Content);

    response->StatusCode = 200;
    
    return response;
}

#endif
