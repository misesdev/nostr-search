#ifndef SERVER_C
#define SERVER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // Para close()
#include <arpa/inet.h>      // Para inet_addr() e htons()
#include <sys/socket.h>     // Para socket(), bind(), listen(), accept()

#define PORT 8080           // Porta que o servidor vai escutar
#define SIZE_BUFFER 1024  // Tamanho do buffer para receber mensagens

int main() {
    int socket_server, new_socket;
    struct sockaddr_in address;
    int size_address = sizeof(address);
    char buffer[SIZE_BUFFER];

    // Resposta HTTP válida
    const char* http_response = 
        "HTTP/1.1 200 OK\r\n"         // Status line
        "Content-Type: application/json\r\n" // Cabeçalho HTTP indicando o tipo de conteúdo
        "Content-Length: 3\r\n"        // Cabeçalho HTTP indicando o tamanho do corpo
        "Access-Control-Allow-Origin: *\r\n"
        "\r\n"                         // Linha em branco para separar os cabeçalhos do corpo
        "Ola";                         // Corpo da mensagem

    // Criando o socket
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_server == 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Definindo o endereço e porta do servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Ligando o socket à porta 8080
    if (bind(socket_server, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Falha no bind");
        close(socket_server);
        exit(EXIT_FAILURE);
    }

    // Escutando por conexões
    if (listen(socket_server, 3) < 0) {
        perror("Falha no listen");
        close(socket_server);
        exit(EXIT_FAILURE);
    }

    printf("Servidor TCP escutando na porta %d\n", PORT);

    while (1) {
        // Aceitando uma nova conexão
        new_socket = accept(socket_server, (struct sockaddr*)&address, (socklen_t*)&size_address);
        if (new_socket < 0) {
            perror("Falha no accept");
            close(socket_server);
            exit(EXIT_FAILURE);
        }

        // Recebendo a mensagem do cliente
        memset(buffer, 0, SIZE_BUFFER);
        int ready = read(new_socket, buffer, SIZE_BUFFER - 1);
        if (ready > 0) {
            printf("Mensagem recebida: %s\n", buffer);

            // Enviando a resposta HTTP válida para o cliente
            send(new_socket, http_response, strlen(http_response), 0);
            printf("Resposta HTTP enviada.\n");
        }

        // Fechando o socket do cliente
        close(new_socket);
    }

    // Fechando o socket do servidor (nunca será alcançado neste exemplo)
    close(socket_server);
    return 0;
}

#endif



