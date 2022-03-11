#include <mpi.h>
#include <math.h>
#include <iostream>
#include <assert.h>

#define ROOT 0

using namespace std;

int main(int argc, char** argv) {
        unsigned long long
                radius = atoll(argv[1]),
                prime = atoll(argv[2]),
                ans = 0, i, j,
                sqrtRadiusHigh = ceil(radius / sqrt(2)),
                Top = floor(radius / sqrt(2)) + 1;

        MPI_Init(NULL, NULL);
        int world_size, world_rank;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        unsigned long long
                low = Top * world_rank / world_size,
                up = Top * (world_rank + 1) / world_size,
                increment;

        j = ceil(sqrt(radius * radius - low * low));
        for(i = low; i < up; i++) {
                if((j - 1) * (j - 1) >= (radius + i) * (radius - i))
                        j -= 1;
                increment = (j - i - 1) % prime;
                ans = (ans + increment) % prime;
        }
        ans = ans % prime;

        MPI_Barrier(MPI_COMM_WORLD);
        unsigned long long sum = 0;
        MPI_Reduce(&ans, &sum, 1, MPI::LONG_LONG_INT, MPI_SUM, ROOT, MPI_COMM_WORLD);
        sum = sum % prime;
        sum = (sum + sum + sqrtRadiusHigh) % prime;
        sum = (sum * 4) % prime;

        if(world_rank == ROOT)
                cout << sum << endl;
}
