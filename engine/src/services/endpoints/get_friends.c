#ifndef GET_FRIENDS_C
#define GET_FRIENDS_C

#include <stdlib.h>
#include "../../types/types.c" 
#include "../../types/user_trie.c"
#include "../../utils/user_utils.c"

HttpResponse* getFriendsFromUser(char *jsonRequest, HttpResponse *response, struct TrieNode *root)
{
    UserIdentity *identity = jsonToIdentity(jsonRequest, response->Content);

    if(!identity) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNodeFromPubkey(root, identity->pubkey);

    if(!userNode) 
    {
        responseMessage(response->Content, "Focal user not found, please provide a existent public key");
        response->StatusCode = 403;
        free(identity);
        return response;
    }

    userListToJson(userNode->user->friends, response->Content);

    response->StatusCode = 200;
    
    free(identity);

    return response;
}

#endif
