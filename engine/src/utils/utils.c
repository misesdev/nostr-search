#ifndef UTILS_C
#define UTILS_C

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include "../types/types.c"

int getRowInteger(char character)
{
    if(isalpha(character))
    {
        return toupper(character) - 'A' + 10;
    }
    return character - '0';
}

uint8_t* hexToBytes(char *hex) 
{
    int length = strlen(hex);
    uint8_t *bytes = malloc((length / 2) * sizeof(uint8_t));

    int index = 0;
    uint8_t decimal;
    for(uint8_t i = 0; i < length; i += 2)
    {
        decimal = getRowInteger(hex[i]) * 16;
        decimal += getRowInteger(hex[i + 1]);
        bytes[index] = decimal;
        index++;
    }

    return bytes; 
}

int parseInt(char *decimal)
{
    int length = strlen(decimal);

    int result = 0;
    int power = 1;
    for(int i = length - 1; i >= 0; i--) {
        result += getRowInteger(decimal[i]) * power;
        power *= 10;
    }
    
    return result;
}

float textSimilarity(char *origin, char *compare)
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    int intersection = 0, number;
    float sizePairs = (strlen(origin) + strlen(compare));
    int hashMap[255] = {0};
    
    while(*origin) { 
        number = toupper(*origin) * toupper(*origin+1);
        hashMap[number % 255] += 1;
        origin++;
    }
    
    while(*compare) { 
        number = toupper(*compare) * toupper(*compare+1);
        hashMap[number % 255] += 1;
        compare++;
    }
    
    for(int i = 0; i < 255; i++)
    {
        if(hashMap[i] > 1) intersection += hashMap[i] / 2;
    }    

    return (2 * intersection) / sizePairs;
}

void compressPubkey(char *pubkey, uint8_t *address)
{
    int index = 0;
    uint8_t *numbers = hexToBytes(pubkey);

    for(int i = 0; i < 30; i += 2) {
        address[index] = (numbers[i] * numbers[i+1]) % TRIE_CHILDREN_LENGTH;
        index++;
    }
    free(numbers);
}

char* strconcat(char *str1, char *str2)
{
    int size_1 = strlen(str1);
    int size_2 = strlen(str2);
    int full_size = size_1 + size_2 + 1; // 1 for null byte

    char *result = malloc(full_size);
  
    strcpy(result, str1);
    strcat(result, str2);
    free(str1);

    return result;
}

bool isEmptyAddress(uint8_t array[ADDRESS_LENGTH])
{
    for(int i = 0; i < ADDRESS_LENGTH; i++) {
        if(array[i] > 0) return false;
    }
    return true;
}


#endif

