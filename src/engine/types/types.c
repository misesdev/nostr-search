#include <stdint.h>

typedef struct {
    char name[30];
    uint8_t npub[32];
} User;

typedef struct {
    char pubkey[64];
    char term[64];
} Search;

