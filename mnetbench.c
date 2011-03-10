#include <mpi.h>
#include <stdio.h>

#include "mnetbench.h"
#include "errors.h"
#include "netbench_master.h"
#include "netbench_client.h"
#include "options.h"

struct option_test_arguments opt_test_args;
char errmsg[NETBENCH_ERR_STR_SIZE];

int main (int argc, char **argv)
{
	int ret = 0, rank, tasknb, rc, pnamelen;
	char pname[MPI_MAX_PROCESSOR_NAME];
	options_t options;

	options = parse_options(argc,argv);
	

	if ((rc = MPI_Init(&argc,&argv)) != MPI_SUCCESS)
	{
		ERR_SET_MSG(errmsg,"MPI_Init");
		goto mpierr;
	}

	MPI_Comm_size(MPI_COMM_WORLD,&tasknb);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Get_processor_name(pname, &pnamelen);

	if (!OPT_GET(options,OPT_FLAG_QUIET))
		fprintf(stdout,"Process %d is %s\n", rank, pname);

	if (rank == NETBENCH_MASTER_RANK)
		ret = netbench_master_run(rank,tasknb,options);
	else
		ret = netbench_client_run(rank,tasknb,options);

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
