#ifndef KEY_EXPANSION
#define KEY_EXPANSION

#include "shared.h"

extern const unsigned int Rcon[][4];

void subWord(word w);

void rotWord(word w);

void keyExpansion(BYTE key[], word w[], keyLength currentKeyLength);

#endif