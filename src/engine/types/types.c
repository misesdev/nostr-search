#ifndef TYPES_C
#define TYPES_C

#include <stdint.h>

typedef struct {
    char name[32];
    char npub[65]; // 64 bytes + byte null end
} User;

typedef struct {
    char pubkey[64];
    char term[64];
} Search;

#endif
