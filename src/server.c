#ifndef SERVER_C
#define SERVER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h> // Para threads
#include <sys/types.h>
#include <sys/sysinfo.h> // Para verificar a memória usada

#define PORT 8080
#define SIZE_BUFFER 1024
#define MAX_THREADS 250  // Limite máximo de threads para controlar o uso de memória

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_info;

// Função para processar cada conexão de cliente em uma thread separada
void* handle_client(void* arg) {
    client_info* client = (client_info*)arg;
    char buffer[SIZE_BUFFER];
    memset(buffer, 0, SIZE_BUFFER);

    int bytes_read = read(client->socket, buffer, SIZE_BUFFER - 1);
    if (bytes_read > 0) {
        printf("Mensagem recebida: %s\n", buffer);

        // Obtenha o JSON dinâmico da função jsonResult
        char* json_response = "{\"name\": \"Mises Dev\", \"age\": 15 }";//jsonResult(NULL); // Passar o root correto se necessário

        // Prepare a resposta HTTP
        char http_response[SIZE_BUFFER];
        snprintf(http_response, SIZE_BUFFER,
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: application/json\r\n"
                 "Content-Length: %zu\r\n"
                 "Access-Control-Allow-Origin: *\r\n"
                 "\r\n"
                 "%s",
                 strlen(json_response), json_response);

        send(client->socket, http_response, strlen(http_response), 0);
        printf("Resposta HTTP enviada.\n");

    }

    close(client->socket);
    free(client);  // Libere a memória alocada para client_info
    return NULL;
}

// Função principal do servidor
int main() {
    int socket_server;
    struct sockaddr_in address;
    int size_address = sizeof(address);

    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server == 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(socket_server, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Falha no bind");
        close(socket_server);
        exit(EXIT_FAILURE);
    }

    if (listen(socket_server, MAX_THREADS) < 0) {
        perror("Falha no listen");
        close(socket_server);
        exit(EXIT_FAILURE);
    }

    printf("Servidor TCP escutando na porta %d\n", PORT);

    while (1) {
        client_info* client = malloc(sizeof(client_info)); // Aloca memória para cada cliente
        if (!client) {
            perror("Falha na alocação de memória para o cliente");
            continue; // Tenta aceitar uma nova conexão
        }

        client->socket = accept(socket_server, (struct sockaddr*)&client->address, (socklen_t*)&size_address);
        if (client->socket < 0) {
            perror("Falha no accept");
            free(client);
            continue; // Tenta aceitar uma nova conexão
        }

        // Cria uma nova thread para cada cliente
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)client) != 0) {
            perror("Falha na criação da thread");
            close(client->socket);
            free(client);
        }

        // Verifica o uso da memória do sistema
        struct sysinfo sys_info;
        sysinfo(&sys_info);
        if (sys_info.freeram < 1024 * 1024 * 500) { // Se a memória livre for menor que 500 MB, aguarde
            printf("Memória baixa, aguardando...\n");
            pthread_join(thread_id, NULL); // Aguarda a thread concluir antes de aceitar novas conexões
        }
    }

    close(socket_server);
    return 0;
}

#endif
