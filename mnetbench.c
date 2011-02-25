#include <mpi.h>
#include <stdio.h>
#include <argp.h>

#include "mnetbench.h"
#include "errors.h"
#include "netbench_master.h"
#include "netbench_client.h"
#include "options.h"

char errmsg[NETBENCH_ERR_STR_SIZE];

int main (int argc, char **argv)
{
	int ret = 0, rank, tasknb, rc;
	options_t options;

	OPT_INIT(options);	
	//OPT_SET(options,OPT_FLAG_DEBUG);
	
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

	if (rank == NETBENCH_MASTER_RANK)
	{
		ret = netbench_master_run(rank, tasknb,options);
	}
	else
	{
		ret = netbench_client_run(rank,tasknb-1,options);
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
