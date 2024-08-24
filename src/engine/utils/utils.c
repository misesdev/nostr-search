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

float stringSimilarity(char *origin, char* compare)
{
    // the documentation hire: http://www.catalysoft.com/articles/StrikeAMatch.html
    char originPair[2];
    char comparePair[2];
    uint8_t intersection = 0;
    uint8_t originLength = strlen(origin) - 1;
    uint8_t compareLength = strlen(compare) - 1;
    float sizePairs = originLength + compareLength;

    for (uint8_t i = 0; i < originLength; i++) { 
        originPair[0] = toupper(origin[i]);
        originPair[1] = toupper(origin[i+1]);
        for(uint8_t c = 0; c < compareLength; c++) {
            comparePair[0] = toupper(compare[c]);
            comparePair[1] = toupper(compare[c+1]);

            if(originPair[0] == comparePair[0] && originPair[1] == comparePair[1]) {
                intersection += 1;
            }
        }
    }

    float similarity = (2 * intersection) / sizePairs;

    return similarity;
}

#endif

