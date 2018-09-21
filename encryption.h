#ifndef ENCRYPTION
#define ENCRYPTION

#include "shared.h"

extern const BYTE mixColumnVector[];

void shiftRows(BYTE state[4][Nb]);

void cipher(BYTE in[4*Nb], BYTE out[4*Nb], word w[], keyLength currentKeyLength);

#endif