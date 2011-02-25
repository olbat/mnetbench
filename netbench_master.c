#include <mpi.h>

#include "netbench_master.h"
#include "options.h"
#include "debug.h"


int netbench_master_run(int rank, int clientsnb, options_t opts)
{
	int test = 42, i = clientsnb;
	while (i--)
	{
		if (i != rank)
		{
			DEBUG(opts,"(m) Send message to %d\n",i);

			MPI_Send(&test, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
		}
	}
	return 0;
}
