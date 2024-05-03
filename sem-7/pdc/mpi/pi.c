#include "mpi.h"
#include <math.h>

#define INTERVALS 10e7
int main(int argc, char *argv[])
{
    int n = INTERVALS, root, numberOfProcesses, i;
    double root, pi, h, sum, x;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &root);

    h = 1.0 / (double)n;
    sum = 0.0;

    for (i = root + 1; i <= n; i += numberOfProcesses)
    {
        x = h * ((double)i + 0.5); // mid point of each interval
        sum += 4.0 / (1.0 + x * x);
    }

    sum = h * sum;

    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (root == 0)
        printf("pi is approximately %.16f",
               pi);

    MPI_Finalize();
    return 0;
}