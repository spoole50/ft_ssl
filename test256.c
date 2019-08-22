#include "sha256.h"

char        *sha256(unsigned char *message, int tBytes);

int     main(void)
{
    sha256(NULL,500);
    return (0);
}