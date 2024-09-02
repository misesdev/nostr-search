#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libwebsockets.h>
#include <jansson.h>

#define MAX_RELAYS 5
#define MAX_MESSAGE_LEN 1024

typedef struct {
    struct lws *wsi;
    char url[256];
} relay_t;

static relay_t relays[MAX_RELAYS];
static int relay_count = 0;

// Callback para lidar com WebSocket events
static int callback_nostr(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            printf("Conexão estabelecida com relay.\n");

            // Enviar comando de assinatura para o relay
            char subscribe_message[MAX_MESSAGE_LEN];
            snprintf(subscribe_message, sizeof(subscribe_message), "[\"REQ\", \"6e468422dfb74a5738702a8823b9b28168abab8655faacb6853cd0ee15deee93\", {\"kinds\": [0, 1]}]");
            lws_write(wsi, (unsigned char *)subscribe_message, strlen(subscribe_message), LWS_WRITE_TEXT);
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:
            printf("Evento recebido do relay: %s\n", (char *)in);

            // Aqui, você pode processar o JSON recebido conforme necessário
            json_error_t error;
            json_t *root = json_loads((char *)in, 0, &error);
            if (root) {
                // Extraia e processe dados do evento
                const char *content = json_string_value(json_object_get(json_array_get(root, 2), "content"));
                if (content) {
                    printf("Conteúdo do evento: %s\n", content);
                }
                json_decref(root);
            } else {
                printf("Erro ao processar JSON: %s\n", error.text);
            }
            break;

        case LWS_CALLBACK_CLIENT_CLOSED:
            printf("Conexão fechada pelo relay.\n");
            break;

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            printf("Client connection error\n");
            break;

        case LWS_CALLBACK_CLOSED:
            printf("Client has closed the connection\n");
            break;

        default:
            break;
    }

    return 0;
}

// Protocolo WebSocket
static struct lws_protocols protocols[] = {
    {
        "nostr-protocol",//"websocket-protocol",
        callback_nostr,
        0,
        MAX_MESSAGE_LEN,
    },
    { NULL, NULL, 0, 0 }
};

// Adicionar um relay à lista
void add_relay(const char *url) {
    if (relay_count < MAX_RELAYS) {
        strncpy(relays[relay_count].url, url, sizeof(relays[relay_count].url) - 1);
        relay_count++;
    } else {
        printf("Máximo de relays atingido.\n");
    }
}

int main(void) {
    struct lws_context *context;
    struct lws_context_creation_info info;

    memset(&info, 0, sizeof(info));
    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    //info.timeout_secs = 60;
    //info.options |= LWS_SERVER_OPTION_DISABLE_IPV6;
    //info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    //info.client_ssl_ca_filepath = NULL;

    // logs detalhados
    lws_set_log_level(LLL_DEBUG | LLL_INFO | LLL_ERR | LLL_WARN, NULL);

    context = lws_create_context(&info);
    if (!context) {
        printf("Falha ao criar o contexto LWS.\n");
        return 1;
    }

    // Adicione relays à lista
    //add_relay("relay.damus.io");
    //add_relay("filter.nostr.wine");
    add_relay("nostr.wine");

    // Conectar a todos os relays
    for (int i = 0; i < relay_count; i++) {
        struct lws_client_connect_info ccinfo = {0};
        ccinfo.context = context;
        ccinfo.address = relays[i].url;
        ccinfo.port = 443; // Porta padrão para WebSocket seguro
        ccinfo.path = "/";
        ccinfo.host = lws_canonical_hostname(context);
        ccinfo.origin = "origin"; //lws_canonical_hostname(context);
        ccinfo.protocol = protocols[0].name;
        ccinfo.ssl_connection = LCCSCF_USE_SSL; //LCCSCF_ALLOW_INSECURE;
        //ccinfo.userdata = &relays[i];

        relays[i].wsi = lws_client_connect_via_info(&ccinfo);
    }

    // Loop principal
    while (relay_count > 0) {
        lws_service(context, 1500);
    }

    lws_context_destroy(context);

    return 0;
}
