#ifndef SERVER_C
#define SERVER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h> 
#include <sys/types.h>
#include <sys/sysinfo.h> 
#include "../utils/http_utils.c"

#define MIN_FREE_MEMORY 1024 * 1024 * 300
#define SIZE_BUFFER 1024 * 10 // 10 kbytes
#define MAX_THREADS 500  // Limite máximo de threads para controlar o uso de memória

typedef struct {
    int socket;
    struct sockaddr_in address;
    HttpResponse* (* executeRequest)(char *, struct TrieNode *);
    struct TrieNode *root;
} client_info;

// Função para processar cada conexão de cliente em uma thread separada
void* handle_client(void* arg) 
{
    client_info* client = (client_info*)arg;
    char *buffer = calloc(SIZE_BUFFER, sizeof(char));
    
    if(!buffer) {
        perror("failed to allocate memory for request buffer");
        close(client->socket);
        free(client);  
        return NULL;
    }

    int bytes_read = read(client->socket, buffer, SIZE_BUFFER);
    
    // Adiciona o terminador NUL no final
    if (bytes_read > 0) 
    {
        logRequest(buffer);
                
        HttpResponse *response = client->executeRequest(buffer, client->root);

        char *http_response = httpResponse(response);

        send(client->socket, http_response, strlen(http_response), 0);

        free(http_response);
        free(response);
    }

    close(client->socket);
    free(buffer);
    free(client);  
    return NULL;
}

// master function of server
void upServer(HttpResponse *(* executeRequest)(char*, struct TrieNode*), struct TrieNode *root, int port) 
{
    int socket_server;
    struct sockaddr_in address;
    int size_address = sizeof(address);

    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server == 0) {
        perror("failed to create the socket\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socket_server, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("failed to bind\n");
        close(socket_server);
        exit(EXIT_FAILURE);
    }

    if (listen(socket_server, MAX_THREADS) < 0) {
        perror("failed to listen\n");
        close(socket_server);
        exit(EXIT_FAILURE);
    }

    printf("tcp server listening in port: %d\n", port);

    while (true) 
    {
        // // Verifica o uso da memória do sistema
        // struct sysinfo sys_info;
        // sysinfo(&sys_info);
        // if (sys_info.freeram < MIN_FREE_MEMORY) { // if free memory for menor que 300 MB, aguarde
        //     //printf("Memória baixa, aguardando...\n");
        //     continue;
        //     //pthread_join(thread_id, NULL); // Aguarda a thread concluir antes de aceitar novas conexões
        // }

        client_info* client = calloc(1, sizeof(client_info)); // Aloca memória para cada cliente
        if (!client) {
            perror("fail in the allocation of memory for the client\n");
            continue; // Tenta aceitar uma nova conexão
        }

        client->socket = accept(socket_server, (struct sockaddr*)&client->address, (socklen_t*)&size_address);
        if (client->socket < 0) {
            perror("failed to accept requests\n");
            free(client);
            continue; // Tenta aceitar uma nova conexão
        }

        client->executeRequest = executeRequest;
        client->root = root;

        // Cria uma nova thread para cada cliente
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)client) != 0) {
            perror("failed to create the thread\n");
            close(client->socket);
            free(client);
        }

        // Verifica o uso da memória do sistema
        struct sysinfo sys_info;
        sysinfo(&sys_info);
        if (sys_info.freeram < MIN_FREE_MEMORY) { // if free memory for menor que 300 MB, aguarde
            printf("Memória baixa, aguardando...\n");
            pthread_join(thread_id, NULL); // Aguarda a thread concluir antes de aceitar novas conexões
        }
    }

    close(socket_server);
}

#endif
