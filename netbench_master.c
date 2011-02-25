#include <mpi.h>
#include <stdio.h>

#include "netbench_master.h"


int netbench_master_run(int rank, int clientsnb)
{
	int test = 42, i = clientsnb;
	while (i--)
	{
		if (i != rank)
		{
			MPI_Send(&test, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			printf("Sent %d to client %d\n",test,i);
		}
	}
	return 0;
}
