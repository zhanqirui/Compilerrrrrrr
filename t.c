#include <stdio.h>
#include <stdint.h>

int main()
{
    union {
        uint64_t i;
        double d;
    } u;
    u.i = 0x4000000000000000;
    printf("%f\n", u.d); // 输出 1.000000
    return 0;
}