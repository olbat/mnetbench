#include <mpi.h>
#include <stdio.h>

#include "gridnetbench.h"
#include "errors.h"
#include "netbench_master.h"
#include "netbench_client.h"

char errmsg[GRID_ERR_STR_SIZE];

int main (int argc, char **argv)
{
	int ret = 0, rank, tasknb, rc;
	
	if (argc < 1)
	{
		fprintf(stderr,"usage: %s <...>\n",*argv);
		goto out;
	}

	if ((rc = MPI_Init(&argc,&argv)) != MPI_SUCCESS)
	{
		ERR_SET_MSG(errmsg,"MPI_Init");
		goto mpierr;
	}

	MPI_Comm_size(MPI_COMM_WORLD,&tasknb);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if (rank == GRID_MASTER_RANK)
	{
		ret = netbench_master_run(rank, tasknb);
	}
	else
	{
		ret = netbench_client_run(rank,tasknb-1);
	}

	MPI_Finalize();

	if (ret)
		goto err;
	else
		goto out;

	mpierr:
		MPI_Abort(MPI_COMM_WORLD, rc);
	err:
		perror(errmsg);
		return 1;
	out:
		return ret;
}
