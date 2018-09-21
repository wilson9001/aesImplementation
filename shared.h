#ifndef SHARED
#define SHARED

//length of bits in a word, divided into 4 bytes
const int wordLength = 32;
//number of bytes in a word
const int Nb = 4;

typedef unsigned char BYTE;

typedef BYTE word[4];

//Use to track selected keyLength and index into Nk and Nr
typedef enum KeyLength
{
    KL128,
    KL192,
    KL256
} keyLength;

//Index into these arrays with the keyLength enum
const int Nk[] = {4, 6, 8};
const int Nr[] = {10, 12, 14};

void addRoundKey(BYTE state[4][Nb], word w[Nb]);

BYTE ffMultiply(BYTE a, BYTE b);

void subBytes(BYTE state [4][Nb], BYTE SubBox[16][16]);

void mixColumns(BYTE state[4][Nb], BYTE mixingVector[4]);

#endif