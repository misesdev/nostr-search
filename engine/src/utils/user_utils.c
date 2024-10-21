#ifndef USER_UTILS_C
#define USER_UTILS_C

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./http_utils.c"
#include "../types/types.c" 
#include "../types/user_list.c"
#include "cjson/cJSON.h"

User* createUser(char *name, char *profile, char *pubkey)
{
    User *user = calloc(1, sizeof(User));
    strcpy(user->profile, profile);
    strcpy(user->pubkey, pubkey);
    strcpy(user->name, name);
    strcpy(user->displayName, name);
    user->friends = NULL;

    return user;
}

void insertFriend(User *user, User *friend)
{
    if(!user->friends) {
        user->friends = createUserNode(friend);
        return;
    }

    struct UserNode *current = user->friends;
    while(current) 
    {
        if(strcmp(current->user->pubkey, friend->pubkey) == 0) return;

        if(!current->next) 
        {
            current->next = createUserNode(friend);
            return;
        }
        
        current = current->next;
    }
}

User* jsonToUser(char *jsonString, char *error) 
{   
    cJSON *json = cJSON_Parse(jsonString);

    if(!json) {
        responseMessage(error, "Error when parsing json, invalid json");
        return NULL;
    }

    User *user = malloc(sizeof(User));

    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON *pubkey = cJSON_GetObjectItemCaseSensitive(json, "pubkey");
    cJSON *profile = cJSON_GetObjectItemCaseSensitive(json, "profile");
    cJSON *displayName = cJSON_GetObjectItemCaseSensitive(json, "displayName");

    if(cJSON_IsString(name) && (name->valuestring != NULL) && 
        cJSON_IsString(pubkey) && (pubkey->valuestring != NULL) && 
        cJSON_IsString(profile) && (profile->valuestring != NULL) &&
        cJSON_IsString(displayName) && (displayName->valuestring != NULL))
    {
        if(strlen(pubkey->valuestring) != 64) {
            responseMessage(error, "Error invalid pubkey, please provide a valid pubkey");
            cJSON_Delete(json);
            free(user);
            return NULL;
        }

        snprintf(user->name, 45, "%s", name->valuestring);
        snprintf(user->pubkey, 65, "%s", pubkey->valuestring);
        snprintf(user->profile, 150, "%s", profile->valuestring);
        snprintf(user->displayName, 45, "%s", displayName->valuestring); 

        user->friends = NULL;
        user->index = 0;
    } 
    else 
    {
        responseMessage(error, "Error when parsing user, expected properties 'name', "
            "'displayName', 'pubkey' and 'profile'");
        cJSON_Delete(json);
        free(user);
        return NULL;
    }

    cJSON_Delete(json);

    return user;
}

cJSON* userToCJSON(User *user)
{
    cJSON *userJson = cJSON_CreateObject();

    cJSON_AddStringToObject(userJson, "name", user->name);
    cJSON_AddStringToObject(userJson, "pubkey", user->pubkey);
    cJSON_AddStringToObject(userJson, "profile", user->profile);
    cJSON_AddStringToObject(userJson, "displayName", user->displayName);

    return userJson;
}

void userToJson(User *user, char *jsonUser)
{
    cJSON *userJson = userToCJSON(user);

    char *jsonResult = cJSON_Print(userJson);

    snprintf(jsonUser, MAX_RESPONSE_LENGTH, "%s", jsonResult);

    cJSON_Delete(userJson);
}

void userListToJson(struct UserNode *rootUsers, char *response)
{
    cJSON *jsonList = cJSON_CreateArray();

    struct UserNode *current = rootUsers;
    while(current) 
    {
        if(current->user)
            cJSON_AddItemToArray(jsonList, userToCJSON(current->user));

        current = current->next;
    }

    snprintf(response, MAX_RESPONSE_LENGTH, "%s", cJSON_Print(jsonList));

    cJSON_Delete(jsonList);
}
                 
UserIdentity* jsonToIdentity(char *json_params, char *error)
{
    cJSON *jsonIdentity = cJSON_Parse(json_params);

    if(!jsonIdentity) {
        responseMessage(error, "Error when parsing json, invalid json");
        return NULL;
    }

    cJSON *pubkey = cJSON_GetObjectItem(jsonIdentity, "pubkey");

    if(!cJSON_IsString(pubkey)) {
        responseMessage(error, "Error when parsing user, expected property 'pubkey'");
        cJSON_Delete(jsonIdentity);
        return NULL;
    }

    if(strlen(pubkey->valuestring) != 64) {
        responseMessage(error, "Error invalid 'pubkey', expected 32 bytes hexadecimal");
        cJSON_Delete(jsonIdentity);
        return NULL;
    }

    UserIdentity *identity = malloc(sizeof(UserIdentity));

    strcpy(identity->pubkey, pubkey->valuestring);

    return identity;    
}

uint32_t getFriendsCount(User *user)
{
    uint32_t count = 0;
    struct UserNode *current = user->friends;
    while(current) 
    {
        if(current->user) count += 1;

        current = current->next;
    }

    return count;
}

void copyUserData(User *origin, User *destination)
{
    snprintf(destination->name, 45, "%s", origin->name);
    snprintf(destination->pubkey, 65, "%s", origin->pubkey);
    snprintf(destination->profile, 150, "%s", origin->profile);
    snprintf(destination->displayName, 45, "%s", origin->displayName);
}


#endif  

