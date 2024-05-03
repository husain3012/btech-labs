#include "omp.h"
#include <stdio.h>

int main(void)
{
    int i, n = 10;
    int fac = 1;
    #pragma omp parallel for shared(n) private(i) reduction(* : fac)
    for (i = 1; i <= n; i++)
    {
        fac *= i;
    }
    printf("factorial = %d\n", fac);
    return 0;
}