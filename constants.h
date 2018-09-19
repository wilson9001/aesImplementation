#ifndef CONSTANTS
#define CONSTANTS

//length of bits in a word, divided into 4 bytes
const int wordLength = 32;
//number of bytes in a word
const int Nb = 4;

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
const int Nk[] = {4, 6, 8};
const int Nr[] = {10, 12, 14};

const Rcon[] = { //TODO: Determine type...
    0x00000000, // Rcon[] is 1-based, so the first entry is just a place holder
    0x01000000, 0x02000000, 0x04000000, 0x08000000,
    0x10000000, 0x20000000, 0x40000000, 0x80000000,
    0x1B000000, 0x36000000, 0x6C000000, 0xD8000000,
    0xAB000000, 0x4D000000, 0x9A000000, 0x2F000000,
    0x5E000000, 0xBC000000, 0x63000000, 0xC6000000,
    0x97000000, 0x35000000, 0x6A000000, 0xD4000000,
    0xB3000000, 0x7D000000, 0xFA000000, 0xEF000000,
    0xC5000000, 0x91000000, 0x39000000, 0x72000000,
    0xE4000000, 0xD3000000, 0xBD000000, 0x61000000,
    0xC2000000, 0x9F000000, 0x25000000, 0x4A000000,
    0x94000000, 0x33000000, 0x66000000, 0xCC000000,
    0x83000000, 0x1D000000, 0x3A000000, 0x74000000,
    0xE8000000, 0xCB000000, 0x8D000000
    };

#endif