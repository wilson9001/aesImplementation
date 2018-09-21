#ifndef DECRYPTION
#define DECRYPTION

#include "shared.h"

extern const BYTE InvSbox[16][16];
extern const BYTE invMixColumnVector[];

void invShiftRows(BYTE state[4][Nb]);

void invCipher(BYTE in[4*Nb], BYTE out[4*Nb], word w[], keyLength currentKeyLength);

#endif