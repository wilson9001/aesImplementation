#ifndef KEY_EXPANSION
#define KEY_EXPANSION

#include "shared.h"

const unsigned int Rcon[];

void subWord(word w);

void rotWord(word w);

void keyExpansion(BYTE key[], word w[], keyLength currentKeyLength);

#endif