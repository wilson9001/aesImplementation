#ifndef ENCRYPTION
#define ENCRYPTION

#include "shared.h"

const BYTE mixColumnVector[4];

void shiftRows(BYTE state[4][Nb]);

void cipher(BYTE in[4*Nb], BYTE out[4*Nb], word w[], keyLength currentKeyLength);

#endif