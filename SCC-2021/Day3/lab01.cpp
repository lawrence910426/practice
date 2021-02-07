#include <mpi.h>
#include <stdio.h>

#define ROOT 0

int sqrt(long long x) {
	long long l = 0, r = x, mid;
	while(l != r - 1) {
		mid = (l + r) >> 1;
		if(mid * mid <= x) l = mid;
		else r = mid;
	}
	return l;
}

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);
	
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	int radius;
	if(world_rank == ROOT) scanf("[ROOT] Input the desired radius: %d", &radius);
	MPI_Bcast(&radius, 1, MPI::INT, ROOT, MPI_COMM_WORLD);

	int ans = 0;
	int low = radius * world_rank / world_size, up = radius * (world_rank + 1) / world_size;
	
	for(int i = low;i < up;i++) 
		ans += sqrt(radius * radius - i * i);
	
	MPI_Barrier(MPI_COMM_WORLD);
	int sum;
	MPI_Reduce(&ans, &sum, 1, MPI::INT, MPI_SUM, ROOT, MPI_COMM_WORLD);
	printf("[%d] The answer is: %d\n", world_rank, sum);
} 
