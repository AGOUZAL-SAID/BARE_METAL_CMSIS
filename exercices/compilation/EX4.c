#include <stdint.h>
#include <stdio.h>

int32_t x = 34;
int32_t y;
const char *mesg = "Hello World!\n";

int main() {
    static uint8_t z;
    uint16_t t;

    y = 12;
    z = z + 1;
    t = y+z;

    printf(mesg);
    printf("x = %d, y = %d, z = %d, t = %d\n",
           x, y, z, t);
    return 0;
}
