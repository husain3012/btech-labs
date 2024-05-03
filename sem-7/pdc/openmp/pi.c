#include "omp.h"
#include <stdio.h>

#define INTERVALS 10e7
int main(int argc, char *argv[])
{
    int n = INTERVALS, i;
    double h, pi, x, sum = 0.0;

    h = 1.0 / (double)n;
    
    #pragma omp parallel for private(x) reduction(+:sum)

    for (i = 1; i <= n; i ++)
    {
        x = h*((double)i + 0.5); // mid point of each interval
        sum += 4.0 / (1.0 + x * x);
    }

    pi = h * sum;
    printf("pi is approximately %.16f", pi);
    return 0;
}