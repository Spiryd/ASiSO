#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2 ){
        printf("Usage: %s <command> \n", argv[0]);
        return 1;
    }
}

setuid(0);
system(argv[1]);
return 0 ;