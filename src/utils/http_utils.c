#ifndef HTTP_UTILS_C
#define HTTP_UTILS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./utils.c"
#include "../types/types.c"

Search* requestParams(char *request) 
{
    char *start = NULL;
    Search *search = malloc(sizeof(Search));

    // Extract  data for GET
    if((start = strstr(request, "GET /?")) != NULL) {
        sscanf(start, "GET /?pubkey=%[^&]&search=%s", search->pubkey, search->search);
    } 
    // Extract data for POST
    else if ((start = strstr(request, "\r\n\r\n")) != NULL) {
        start += 4; // skip the "\r\n\r\n"
        sscanf(start, "pubkey=%[^&]&search=%s", search->pubkey, search->search);
    } 
    else return NULL;

    if(strlen(search->pubkey) < 64) return NULL;
    if(strlen(search->search) < 5) return NULL;

    return search; 
}

char* jsonResult(struct UserNode *root)
{
    char *response = malloc(2 * sizeof(char)); 

    strcpy(response, "[");

    struct UserNode *current = root;
    
    while (current) 
    {     
        if(current->user) {
            // build property username
            response = strconcat(response, "{ \"username\":\""); 
            response = strconcat(response, current->user->name); 
            response = strconcat(response, "\", ");

            // build the property pubkey
            response = strconcat(response, "\"pubkey\":\"");
            response = strconcat(response, current->user->pubkey); 
            response = strconcat(response, "\", ");
        
            // build the property profile
            response = strconcat(response, "\"profile\":\"");
            response = strconcat(response, current->user->profile);
            response = strconcat(response, "\"}");
        
            if(current->next != NULL) {
                response = strconcat(response, ",");
            }
        }

        current = current->next;
    }

    response = strconcat(response, "]");

    return response; 
}

char* httpResponse(char *json_result)
{
    char *response = malloc(1024 * sizeof(char));
    
    snprintf(response, 2048,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %zu\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "\r\n"
        "%s",
        strlen(json_result), 
        json_result
    );

    return response;
}

void logRequest(char *buffer) 
{
    char log[100];
    char *start = NULL;
    
    if((start = strstr(buffer, "Host:")) != NULL) {
        sscanf(start, "Host:%s", log);
        printf("received request from: %s\n", log);
    }
}

#endif


