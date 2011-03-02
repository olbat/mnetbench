#include <mpi.h>
#include <stdlib.h>

#include "netbench_test_bandwidth.h"
#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_result_bandwidth.h"
#include "debug.h"
#include "options.h"


struct netbench_test_data *
netbench_test_bandwidth_init(int opts)
{
	struct netbench_test_data *ret;
	ret = (__typeof__(ret)) malloc(sizeof(__typeof__(ret)));

	ret->type = NETBENCH_TEST_BANDWIDTH;
	ret->u.bandwidth = (struct netbench_test_bandwidth *)
		malloc(sizeof(struct netbench_test_bandwidth));

	ret->u.bandwidth = (struct netbench_test_bandwidth *)
		malloc(sizeof(struct netbench_test_bandwidth));

	return ret;
}

void netbench_test_bandwidth_free(struct netbench_test_data *data)
{
	free(data->u.bandwidth);
	free(data);
}

int netbench_test_bandwidth_reset(struct netbench_test_data *data)
{
	return 0;
}

int netbench_test_bandwidth_tester_run(
	int mrank,
	int trank,
	struct netbench_result *res,
	struct netbench_test_data *dat,
	unsigned int repeat,
	int opts
)
{
	int test;
	struct netbench_result_bandwidth *resptr;
	resptr = res->u.bandwidth;
	struct netbench_test_bandwidth *datptr;
	datptr = dat->u.bandwidth;

	datptr->average = 1;
	resptr->bw = 1;
	test = 42;

	DEBUG(opts,"(%d) Send message %d to %d\n",mrank,test,trank);
	MPI_Send(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	
	return 0;
}

int netbench_test_bandwidth_tested_run(
	int mrank,
	int trank,
	struct netbench_test_data *dat,
	unsigned int repeat,
	int opts
)
{
	int test;
	struct netbench_test_bandwidth *datptr;
	MPI_Status stat;
	datptr = dat->u.bandwidth;

	datptr->average = 1;

	DEBUG(opts,"(%d) Waiting message from %d\n",mrank,trank);
	MPI_Recv(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
	DEBUG(opts,"(%d) Got %d from %d\n",mrank,test,trank);
	
	return 0;
}
