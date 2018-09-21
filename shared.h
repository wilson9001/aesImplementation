#ifndef SHARED
#define SHARED

//number of bytes in a word
#define Nb 4

typedef unsigned char BYTE;
typedef BYTE word[Nb];
//Use to track selected keyLength and index into Nk and Nr
typedef enum KeyLength
{
    KL128,
    KL192,
    KL256
} keyLength;

//Index into these arrays with the keyLength enum
const int Nk[3];
const int Nr[3];
//length of bits in a word, divided into 4 bytes
const int wordLength;
const BYTE MODULO;
const BYTE bitTest[8]; //test for which bits in b are set
const BYTE Sbox[16][16];

void addRoundKey(BYTE state[4][Nb], word w[Nb]);//may need to make just word w[]...

BYTE ffMultiply(BYTE a, BYTE b);

void subBytes(BYTE state [4][Nb], const BYTE SubBox[16][16]);

void mixColumns(BYTE state[4][Nb], const BYTE mixingVector[4]);

BYTE xtime(BYTE in);

#endif