#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // Para close()
#include <arpa/inet.h>      // Para inet_addr() e htons()
#include <sys/socket.h>     // Para socket(), bind(), listen(), accept()

#define PORTA 8080           // Porta que o servidor vai escutar
#define TAMANHO_BUFFER 1024  // Tamanho do buffer para receber mensagens

int main() {
    int socket_servidor, novo_socket;
    struct sockaddr_in endereco;
    int tamanho_endereco = sizeof(endereco);
    char buffer[TAMANHO_BUFFER];

    // Resposta HTTP válida
    const char* resposta_http = 
        "HTTP/1.1 200 OK\r\n"         // Status line
        "Content-Type: application/json\r\n" // Cabeçalho HTTP indicando o tipo de conteúdo
        "Content-Length: 3\r\n"        // Cabeçalho HTTP indicando o tamanho do corpo
        "Access-Control-Allow-Origin: *\r\n"
        "\r\n"                         // Linha em branco para separar os cabeçalhos do corpo
        "Ola";                         // Corpo da mensagem

    // Criando o socket
    socket_servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_servidor == 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Definindo o endereço e porta do servidor
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(PORTA);

    // Ligando o socket à porta 8080
    if (bind(socket_servidor, (struct sockaddr*)&endereco, sizeof(endereco)) < 0) {
        perror("Falha no bind");
        close(socket_servidor);
        exit(EXIT_FAILURE);
    }

    // Escutando por conexões
    if (listen(socket_servidor, 3) < 0) {
        perror("Falha no listen");
        close(socket_servidor);
        exit(EXIT_FAILURE);
    }

    printf("Servidor TCP escutando na porta %d\n", PORTA);

    while (1) {
        // Aceitando uma nova conexão
        novo_socket = accept(socket_servidor, (struct sockaddr*)&endereco, (socklen_t*)&tamanho_endereco);
        if (novo_socket < 0) {
            perror("Falha no accept");
            close(socket_servidor);
            exit(EXIT_FAILURE);
        }

        // Recebendo a mensagem do cliente
        memset(buffer, 0, TAMANHO_BUFFER);
        int leitura = read(novo_socket, buffer, TAMANHO_BUFFER - 1);
        if (leitura > 0) {
            printf("Mensagem recebida: %s\n", buffer);

            // Enviando a resposta HTTP válida para o cliente
            send(novo_socket, resposta_http, strlen(resposta_http), 0);
            printf("Resposta HTTP enviada.\n");
        }

        // Fechando o socket do cliente
        close(novo_socket);
    }

    // Fechando o socket do servidor (nunca será alcançado neste exemplo)
    close(socket_servidor);
    return 0;
}





