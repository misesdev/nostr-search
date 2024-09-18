#ifndef UP_FRIENDS_C
#define UP_FRIENDS_C

#include "../../types/types.c"
#include "../../types/user_trie.c"
#include "../../utils/user_utils.c"
#include "../../utils/friends_utils.c"

#include <stdio.h>
#include <stdlib.h>

HttpResponse* insertFriends(char *request, struct TrieNode *root)
{
    HttpResponse *response = calloc(1, sizeof(HttpResponse));
    
    struct FriendNode *friends = jsonToFriends(request, response->Content);

    if(!friends) {
        response->StatusCode = 403;
        return response;
    }

    struct TrieNode *userNode = getTrieNode(root, friends->address);

    if(!userNode)
    {
        responseMessage(response->Content, "User not found");
        response->StatusCode = 204;
        free(friends);
        return response;
    }

    printf("username: %s\n", userNode->user->displayName);

    struct FriendNode *current = friends->next;
    while(current)
    {
        struct TrieNode *friendNode = getTrieNode(root, current->address);

        if(friendNode) {
            insertFriend(userNode->user, friendNode->user);
            printf("    friend: %s\n", friendNode->user->displayName);
        }
        current = current->next;
    }

    responseMessage(response->Content, "add friends succefully");
    response->StatusCode = 200; 

    free(friends);
    
    return response;
}

#endif
