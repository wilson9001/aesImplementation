#ifndef ENCRYPTION
#define ENCRYPTION

#include "constants.h"

void subBytes(BYTE** state /*[4][Nb]*/);

void shiftRows(BYTE** state/*[4][Nb]*/);

BYTE ffMultiply(BYTE a, BYTE b);

void mixColumns(BYTE** state/*[4][Nb]*/);

void addRoundKey(BYTE** state/*[4][Nb]*/, word* w);

void cipher(BYTE* in/*[4*Nb]*/, BYTE* out/*[4*Nb]*/, word* w, keyLength currentKeyLength);

#endif