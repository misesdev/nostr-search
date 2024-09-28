#ifndef SAVE_UTILS_C
#define SAVE_UTILS_C

#include <cjson/cJSON.h>
#include <string.h>

#include "./http_utils.c"

int getScopeFromJson(char *jsonRequest, char *error)
{
    cJSON *jsonParams = cJSON_Parse(jsonRequest);

    if(!jsonParams) {
        responseMessage(error, "Error invalid json");
        return 0;
    }

    cJSON *scope = cJSON_GetObjectItem(jsonParams, "scope");

    if(!cJSON_IsString(scope)) {
        responseMessage(error, "Error expected the property 'scope'");
        cJSON_Delete(jsonParams);
        return 0;
    }

    if(strcmp(scope->valuestring, "users") != 0 &&
       strcmp(scope->valuestring, "friends") != 0 &&
       strcmp(scope->valuestring, "relays") != 0
    ) {
        responseMessage(error, "Error, expected scopes 'users', 'relays' or 'friends'");
        cJSON_Delete(jsonParams);
        return 0;
    }

    if(strcmp(scope->valuestring, "users") == 0) return SCOPE_USERS;
    if(strcmp(scope->valuestring, "friends") == 0) return SCOPE_FRIENDS;
    
    return SCOPE_RELAYS;
}


#endif
