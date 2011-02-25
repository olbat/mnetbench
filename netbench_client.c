#include <mpi.h>
#include <stdio.h>

#include "netbench_client.h"
#include "gridnetbench.h"

int netbench_client_run(int rank, int clientsnb)
{
	int test;
	MPI_Status stat;
	MPI_Recv(&test, 1, MPI_INT, GRID_MASTER_RANK, 1, MPI_COMM_WORLD,&stat);
	printf("Received %d from master\n",test);
	return 0;
}
