#ifndef UTILS_C
#define UTILS_C

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>

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

float stringSimilarity(char origin[], char compare[])
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    uint8_t intersection = 0;
    float sizePairs = strlen(origin) + strlen(compare);

    for (uint8_t i = 0; origin[i] != '\0'; i++) { 
        for(uint8_t c = 0; compare[c] != '\0'; c++) {
            if(toupper(origin[i]) == toupper(compare[c])
                && toupper(origin[i+1]) == toupper(compare[c+1])) {
                intersection++;
            }
        }
    }

    float similarity = (2 * intersection) / sizePairs;

    return similarity;
}

float textSimilarity(char *origin, char *compare)
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    int intersection = 0, number;
    float sizePairs = (strlen(origin) + strlen(compare));
    int hashMap[50] = {0};
    
    while(*origin) { 
        number = toupper(*origin) * toupper(*origin+1);
        hashMap[number % 50] += 1;
        origin++;
    }
    
    while(*compare) { 
        number = toupper(*compare) * toupper(*compare+1);
        hashMap[number % 50] += 1;
        compare++;
    }
    
    for(int i = 0; i < 50; i++)
    {
        if(hashMap[i] > 1) intersection += hashMap[i] / 2;
    }    

    return (2 * intersection) / sizePairs;
}

uint8_t* compressPubkey(char *pubkey)
{
    uint8_t index = 0;
    uint8_t *address = malloc(16 * sizeof(uint8_t));
    uint8_t *numbers = hexToBytes(pubkey);

    for(uint8_t i = 0; i < 32; i += 2) {
        address[index] = (numbers[i] * numbers[i+1]) % 200;
        index++;
    }
    free(numbers);

    return address;
}

#endif

