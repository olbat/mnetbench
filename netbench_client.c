#include <mpi.h>
#include <stdio.h>

#include "netbench_client.h"
#include "options.h"
#include "debug.h"
#include "mnetbench.h"

int netbench_client_run(int rank, int clientsnb, options_t opts)
{
	int test;
	MPI_Status stat;
	DEBUG(opts,"(%d) Waiting for master's message\n",rank);

	MPI_Recv(&test, 1, MPI_INT, NETBENCH_MASTER_RANK, 1, MPI_COMM_WORLD,&stat);

	DEBUG(opts,"(%d) Got %d from master\n",rank,test);
	return 0;
}
