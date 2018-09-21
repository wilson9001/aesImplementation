#include <stdio.h>
#include "shared.h"
#include "encryption.h"
#include "decryption.h"
#include "keyExpansion.h"

int main(int argc, char const *argv[])
{
    printf("Beginning Finite Field Tests\n\txtime:\n\t\txtime(0x57) == 0xae\n\t\t");

    printf("0x%x", xtime(0x57));

    printf("\n\t\txtime(0xae) == 0x47\n\t\t");

    printf("0x%x", xtime(0xae));

    printf("\n\t\txtime(0x47) == 0x8e\n\t\t");

    printf("0x%x", xtime(0x47));

    printf("\n\t\txtime(0x8e) == 0x07\n\t\t");

    printf("0x%x", xtime(0x8e));

    printf("\n\tffMultiply:\n\t\tffMultiply(0x57,0x13) == 0xfe");

    printf("\n\t\t0x%x", ffMultiply(0x57, 0x13));

    printf("\nEnd finite field tests");
    
    printf("\nBegin Key Expansion Tests\n\tSubWord:\n\t\tsubWord(0x00102030) == 0x63cab704");

    word test = {0x00, 0x10, 0x20, 0x30};

    subWord(test);

    printf("\n\t\t0x%02x%02x%02x%02x", test[0], test[1], test[2], test[3]);

    printf("\n\t\tsubWord(0x40506070) == 0x0953d051");

    test[0] = 0x40; test[1] = 0x50; test[2] = 0x60; test[3] = 0x70;

    subWord(test);

    printf("\n\t\t0x%02x%02x%02x%02x", test[0], test[1], test[2], test[3]);

    printf("\n\t\tsubWord(0x8090a0b0) == 0xcd60e0e7");

    test[0] = 0x80; test[1] = 0x90; test[2] = 0xa0; test[3] = 0xb0;

    subWord(test);

    printf("\n\t\t0x%02x%02x%02x%02x", test[0], test[1], test[2], test[3]);

    printf("\n\t\tsubWord(0xc0d0e0f0) == 0xba70e18c");

    test[0] = 0xc0; test[1] = 0xd0; test[2] = 0xe0; test[3] = 0xf0;

    subWord(test);

    printf("\n\t\t0x%02x%02x%02x%02x", test[0], test[1], test[2], test[3]);

    printf("\n\tRotWord:\n\t\trotWord(0x09cf4f3c) == 0xcf4f3c09");

    test[0] = 0x09; test[1] = 0xcf; test[2] = 0x4f; test[3] = 0x3c;

    rotWord(test);

    printf("\n\t\t0x%02x%02x%02x%02x", test[0], test[1], test[2], test[3]);

    printf("\n\t\trotWord(0x2a6c7605) == 0x6c76052a");

    test[0] = 0x2a; test[1] = 0x6c; test[2] = 0x76; test[3] = 0x05;

    rotWord(test);

    printf("\n\t\t0x%02x%02x%02x%02x", test[0], test[1], test[2], test[3]);

    printf("\n\tKey Expansion:\n\t\t128 Bit key[16] = \n\t\t{ 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,\n\t\t0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c }\n\t\t");

    printf("Key Expanded[44] = \n\t\t0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c,\n\t\t0xa0fafe17, 0x88542cb1, 0x23a33939, 0x2a6c7605,\n\t\t0xf2c295f2, 0x7a96b943, 0x5935807a, 0x7359f67f,\n\t\t0x3d80477d, 0x4716fe3e, 0x1e237e44, 0x6d7a883b,\n\t\t0xef44a541, 0xa8525b7f, 0xb671253b, 0xdb0bad00,\n\t\t0xd4d1c6f8, 0x7c839d87, 0xcaf2b8bc, 0x11f915bc,\n\t\t0x6d88a37a, 0x110b3efd, 0xdbf98641, 0xca0093fd,\n\t\t0x4e54f70e, 0x5f5fc9f3, 0x84a64fb2, 0x4ea6dc4f,\n\t\t0xead27321, 0xb58dbad2, 0x312bf560, 0x7f8d292f,\n\t\t0xac7766f3, 0x19fadc21, 0x28d12941, 0x575c006e,\n\t\t0xd014f9a8, 0xc9ee2589, 0xe13f0cc8, 0xb6630ca6,\n");

    BYTE key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

    word w[44];

    keyExpansion(key, w, KL128);

    for(int Word = 0; Word < 44; Word++)
    {
        if(Word % 4 == 0)
        {
            printf("\n\t\t");
        }

        printf("0x%02x%02x%02x%02x, ", w[Word][0], w[Word][1], w[Word][2], w[Word][3]);
    }

    printf("\n\tBegin Cipher Tests\n\t\tstate[4][4] =  {\n\t\t{0x19,0xa0,0x9a,0xe9},\n\t\t{0x3d,0xf4,0xc6,0xf8},\n\t\t{0xe3,0xe2,0x8d,0x48},\n\t\t{0xbe,0x2b,0x2a,0x08}}");

    printf("\n\n\t\tsub[4][4] =    {\n\t\t{0xd4,0xe0,0xb8,0x1e},\n\t\t{0x27,0xbf,0xb4,0x41},\n\t\t{0x11,0x98,0x5d,0x52},\n\t\t{0xae,0xf1,0xe5,0x30}}\n");

    BYTE state[4][4] =  { {0x19,0xa0,0x9a,0xe9},
                         {0x3d,0xf4,0xc6,0xf8},
                         {0xe3,0xe2,0x8d,0x48},
                         {0xbe,0x2b,0x2a,0x08}};

    subBytes(state, Sbox);

    for(int row = 0; row < 4; row++)
    {
        printf("\n\t\t{0x%02x,0x%02x,0x%02x,0x%02x},", state[row][0], state[row][1], state[row][2], state[row][3]);
    }

    printf("\n\n\t\tshift[4][4] =  {\n\t\t{0xd4, 0xe0, 0xb8, 0x1e},\n\t\t{0xbf, 0xb4, 0x41, 0x27},\n\t\t{0x5d, 0x52, 0x11, 0x98},\n\t\t{0x30, 0xae, 0xf1, 0xe5}}\n");

    shiftRows(state);

    for(int row = 0; row < 4; row++)
    {
        printf("\n\t\t{0x%02x, 0x%02x, 0x%02x, 0x%02x},", state[row][0], state[row][1], state[row][2], state[row][3]);
    }

    printf("\n\n\t\tBYTE mix[4][4] =    {\n\t\t{0x04, 0xe0, 0x48, 0x28},\n\t\t{0x66, 0xcb, 0xf8, 0x06},\n\t\t{0x81, 0x19, 0xd3, 0x26},\n\t\t{0xe5, 0x9a, 0x7a, 0x4c}}\n");

    mixColumns(state, mixColumnVector);

    for(int row = 0; row < 4; row++)
    {
        printf("\n\t\t{0x%02x, 0x%02x, 0x%02x, 0x%02x},", state[row][0], state[row][1], state[row][2], state[row][3]);
    }
    
    printf("\n\n\t\tBYTE round[4][4] =   {\n\t\t{0xa4, 0x68, 0x6b, 0x02},\n\t\t{0x9c, 0x9f, 0x5b, 0x6a},\n\t\t{0x7f, 0x35, 0xea, 0x50},\n\t\t{0xf2, 0x2b, 0x43, 0x49}}\n");

    addRoundKey(state, &w[0]);

    for(int row = 0; row < 4; row++)
    {
        printf("\n\t\t{0x%02x, 0x%02x, 0x%02x, 0x%02x},", state[row][0], state[row][1], state[row][2], state[row][3]);
    }

    printf("\n\n");
    return 0;
}
