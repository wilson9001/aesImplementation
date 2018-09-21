#include <stdio.h>
#include "shared.h"
#include "encryption.h"
#include "decryption.h"

int main(int argc, char const *argv[])
{
    printf("Beginning Shared Tests\n\txtime:\n\t\txtime(0x57) == 0xae\n\t\t");

    printf("%x", xtime(0x57));

    printf("\n\t\txtime(0xae) == 0x47\n\t\t");

    printf("%x", xtime(0xae));

    printf("\n\t\txtime(0x47) == 0x8e\n\t\t");

    printf("%x", xtime(0x47));

    printf("\n\t\txtime(0x8e) == 0x07\n\t\t");

    printf("%x", xtime(0x8e));

    printf("\n\tffMultiply:\n\t\tffMultiply(0x57,0x13) == 0xfe\n\t\t");

    printf("%x", ffMultiply(0x57, 0x13));

    return 0;
}
