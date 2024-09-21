#ifndef SEARCH_FRIENDS_C
#define SEARCH_FRIENDS_C

#include <stdlib.h>
#include "../../types/types.c" 
#include "../../types/user_trie.c"
#include "../../utils/search_utils.c"

HttpResponse* searchFriends(char *jsonRequest, HttpResponse *response, struct TrieNode *root)
{
    Search *searchParams = getSearchParams(jsonRequest, response->Content);

    if(!searchParams) 
    {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNodeFromPubkey(root, searchParams->pubkey);

    if(!userNode) 
    {
        responseMessage(response->Content, "Focal user not found, please provide a valid public key");
        response->StatusCode = 403;
        free(searchParams);
        return response;
    }

    struct ResultNode *resultListUsers = searchOnFriends(userNode->user, searchParams->search, searchParams->limit);

    resultToJson(resultListUsers, response->Content);
    
    response->StatusCode = 200;
    free(searchParams);

    return response;
}

#endif



