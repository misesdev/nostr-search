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

#define MIN_FREE_MEMORY 1024 * 1024 * 100
#define SIZE_BUFFER 1024 * 10 // 10 kbytes
#define MAX_THREADS 50  // Limite máximo de threads para controlar o uso de memória

typedef struct {
    int socket;
    struct sockaddr_in address;
    HttpResponse* (* executeRequest)(char *, Database *);
    Database *root;
} client_info;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

// Fila de conexões de clientes
client_info* client_queue[MAX_THREADS];
int queue_size = 0;  // Tamanho da fila de clientes

// Função para processar cada cliente em uma thread do pool
void* thread_worker(void* arg) 
{
    while (1) {
        client_info* client;

        pthread_mutex_lock(&queue_mutex);

        // Espera até que haja um cliente na fila
        while (queue_size == 0) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        // Pega um cliente da fila
        client = client_queue[--queue_size];

        pthread_mutex_unlock(&queue_mutex);

        // Processa a requisição
        if (client) {
            char *buffer = calloc(SIZE_BUFFER, sizeof(char));

            if(!buffer) {
                perror("failed to allocate memory for request buffer");
                close(client->socket);
                free(client);  
                continue;
            }

            int bytes_read = read(client->socket, buffer, SIZE_BUFFER);
            if (bytes_read > 0) {
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
        }
    }
    return NULL;
}

// Função para adicionar um cliente à fila de processamento
void enqueue_client(client_info* client) {
    pthread_mutex_lock(&queue_mutex);

    if (queue_size < MAX_THREADS) {
        client_queue[queue_size++] = client;
        pthread_cond_signal(&queue_cond);  // Sinaliza que há um cliente na fila
    } else {
        // Se o pool está cheio, descarta o cliente
        perror("client queue is full, dropping connection");
        close(client->socket);
        free(client);
    }

    pthread_mutex_unlock(&queue_mutex);
}

// master function of server
void upServer(HttpResponse *(* executeRequest)(char*, Database*), Database *root, int port) 
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

    // Cria o pool de threads
    pthread_t thread_pool[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&thread_pool[i], NULL, thread_worker, NULL);
    }

    while (true) 
    {
 
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

        // Adiciona o cliente à fila para ser processado por uma thread
        enqueue_client(client);
    }

    close(socket_server);
}

#endif
