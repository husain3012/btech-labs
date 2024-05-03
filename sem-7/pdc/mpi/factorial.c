#include "mpi.h"
#include <math.h>

double factorial(int start, int end)
{
    double result = 1;
    for(int i = start; i <= end; i++)
    {
        result *= i;
    }
    return result;
}

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number;
    scanf("%d", &number);

    int value_per_process = number / size;
    int start = rank * value_per_process + 1;
    int end = (rank + 1) * value_per_process;

    unsigned long long local_factorial = factorial(start, end);

    unsigned long long global_factorial = 1;

    MPI_Reduce(&local_factorial, &global_factorial, 1, MPI_UNSIGNED_LONG_LONG, MPI_PROD, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Factorial of %d is %llu\n", number, global_factorial);
    }

    MPI_Finalize();
    return 0;



}