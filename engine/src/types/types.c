#ifndef TYPES_C
#define TYPES_C

#define MAX_RESPONSE_LENGTH 2048
#define TRIE_CHILDREN_LENGTH 255
#define ADDRESS_LENGTH 16

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    char name[35];
    char pubkey[65]; // 64 bytes + byte null end
    char profile[100];
    struct UserNode *friends;
} User;

struct UserNode {
    User *user;
    struct UserNode *next;
};

struct TrieNode {
    User *user;
    uint8_t key;
    bool isEndOfKey;
    struct TrieList *childrens;
};

struct TrieList {
    struct TrieNode *node;
    struct TrieList *next;
};

typedef struct {
    char pubkey[65];
    char search[100];
} Search;

typedef  struct {
    int StatusCode;
    char Content[MAX_RESPONSE_LENGTH];
} HttpResponse;

#endif



