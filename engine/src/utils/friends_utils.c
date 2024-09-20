
#ifndef FRIENDS_UTILS_C
#define FRIENDS_UTILS_C

#include "./utils.c"
#include "./http_utils.c"
#include "../types/types.c"
#include "../utils/http_utils.c"

#include <cjson/cJSON.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct FriendNode* createFriendNode(char *pubkey)
{
    struct FriendNode* node = calloc(1, sizeof(struct FriendNode));
    
    compressPubkey(pubkey, node->address);

    node->next = NULL;

    return node;
}

struct FriendNode* invalidPubkey(cJSON *json, struct FriendNode *friends, char *error) 
{
    responseMessage(error, "One invalid pubkey");
    cJSON_Delete(json);
    free(friends);
    
    return NULL;
}

struct FriendNode* jsonToFriends(char *json_params, char *error)
{
    cJSON *jsonFriends = cJSON_Parse(json_params);

    if(!jsonFriends) {
        responseMessage(error, "Error when parsing json, invalid json properties");
        return NULL;
    }
    
    cJSON *pubkey = cJSON_GetObjectItem(jsonFriends, "pubkey");
    cJSON *friends = cJSON_GetObjectItem(jsonFriends, "friends");

    if(!cJSON_IsString(pubkey)) 
    {
        responseMessage(error, "Expectd propertie 'pubkey'");
        cJSON_Delete(jsonFriends);
        return NULL;
    }

    if(!cJSON_IsArray(friends)) {
        responseMessage(error, "Expectd propertie 'friends', an array with pubkeys");
        cJSON_Delete(jsonFriends);
        return NULL;
    }

    struct FriendNode *userFriends = createFriendNode(pubkey->valuestring);

    int friendsCount = cJSON_GetArraySize(friends);

    struct FriendNode *current = userFriends;

    for(int i = 0; i < friendsCount - 1; i++) 
    {
        cJSON *npub = cJSON_GetArrayItem(friends, i);

        if(!cJSON_IsString(npub))
            return invalidPubkey(jsonFriends, userFriends, error);   

        if(strlen(npub->valuestring) < 64)
            return invalidPubkey(jsonFriends, userFriends, error);   

        current->next = createFriendNode(npub->valuestring);
        current = current->next;
    }

    cJSON_Delete(jsonFriends);

    return userFriends;
}


#endif
