#ifndef HTTP_UTILS_C
#define HTTP_UTILS_C

#define HTTP_STATUS_OK 200
#define HTTP_STATUS_BAD_REQUEST 400
#define HTTP_STATUS_FORBIDDEN 403
#define HTTP_STATUS_NOT_FOUND 404
#define HTTP_STATUS_UNAUTHORIZED 401
#define HTTP_STATUS_INTERNAL_ERROR 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/types.c"


bool isPostRequest(char *request)
{
    return (strstr(request, "POST") != NULL);
}

char* requestParams(char *request, char *error) 
{
    char *jsonResult = NULL;

    if(!isPostRequest(request))
    {
        strcpy(error, "Expected POST request with Content-Type: application/json");
        return NULL;
    }

    if ((jsonResult = strstr(request, "\r\n\r\n")) != NULL)
        jsonResult += 4;
    else {
        strcpy(error, "Expected JSON content format");
        return NULL;
    }

    return jsonResult; 
}

char * getStatusCode(int status) 
{
    switch(status) {
        case HTTP_STATUS_OK:
            return "200 OK";
        case HTTP_STATUS_UNAUTHORIZED:
           return "401 Unauthorized";
        case HTTP_STATUS_FORBIDDEN: 
            return "403 Forbidden"; 
        case HTTP_STATUS_NOT_FOUND:
            return "404 Not Found";
        case HTTP_STATUS_BAD_REQUEST:
            return "400 Bad Request";
        case HTTP_STATUS_INTERNAL_ERROR:
            return "500 Internal Server Error";
    }

    return "500 Internal Server Error";
}

char* httpResponse(HttpResponse *json_result)
{
    char *response = malloc(MAX_RESPONSE_LENGTH * sizeof(char));

    char *statusResponse = getStatusCode(json_result->StatusCode);
    
    snprintf(response, MAX_RESPONSE_LENGTH * 2,
        "HTTP/1.1 %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %zu\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "\r\n"
        "%s",
        statusResponse,
        strlen(json_result->Content), 
        json_result->Content
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


