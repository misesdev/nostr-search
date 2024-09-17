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
#include "utils.c"

User* createUser(char *name, char *profile, char *pubkey)
{
    User *user = malloc(sizeof(User));
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
        if(!current->next) {
            current->next = createUserNode(friend);
            break;
        }
        current = current->next;
    }
}

void showUsersOfTrie(struct TrieNode *root)
{
    struct TrieList *list = root->childrens;

    while(list) {
        showUsersOfTrie(list->node);
        list = list->next;
    }

    long users = 0;
    if(root->isEndOfKey) {
        uint8_t address[ADDRESS_LENGTH];
        compressPubkey(root->user->pubkey, address);
        printf("username: %s\n", root->user->name);
        struct UserNode *friends = root->user->friends;
        while(friends) {
            printf("    friend: %s\n", friends->user->name);
            friends = friends->next;
        }
        users++;
    }
}

User* jsonToUser(char *jsonString, char *error) 
{   
    cJSON *json = cJSON_Parse(jsonString);

    if(!json) {
        strcpy(error, "{ \"message\": \"Error when parsing json, expected properties 'name', 'displayName', 'pubkey' and 'profile'\" }");
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
        snprintf(user->name, 45, "%s", name->valuestring);
        snprintf(user->pubkey, 65, "%s", pubkey->valuestring);
        snprintf(user->profile, 150, "%s", profile->valuestring);
        snprintf(user->displayName, 45, "%s", displayName->valuestring);
        
    } 
    else 
    {
        strcpy(error, "{ \"message\": \"Error when parsing user, expected properties 'name', 'displayName', 'pubkey' and 'profile'\" }");
        cJSON_Delete(json);
        free(user);
        return NULL;
    }

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

char* userToJson(User *user)
{
    cJSON *userJson = userToCJSON(user);

    char *jsonResult = cJSON_Print(userJson);

    cJSON_Delete(userJson);

    return jsonResult;
}

char* userListToJson(struct UserNode *root)
{
    cJSON *jsonList = cJSON_CreateArray();

    struct UserNode *current = root;
    while(current) {
        if(current->user) {
            cJSON_AddItemToArray(jsonList, userToCJSON(current->user));
        }
        current = current->next;
    }

    char *jsonResult = cJSON_Print(jsonList);

    cJSON_Delete(jsonList);
    
    return jsonResult;
}
                 
User* getUserFromRequest(char *request, char *error) 
{
    char *json_params = requestParams(request, error);
    
    if(!json_params) return NULL;
        
    User *user = jsonToUser(json_params, error);

    if(!user) return NULL;

    return user;
}


#endif  

