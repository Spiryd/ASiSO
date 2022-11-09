#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 256; i++)
    {
        printf("\x1B[38;5;<%i>mHello World\n", i);
    }

    printf("\x1b[32mHello, World\n");
    
    return 0;
}
