#include <mpi.h>
#include <stdlib.h>

#include "netbench_test_latency.h"
#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_result_latency.h"
#include "debug.h"


struct netbench_test_data *
netbench_test_latency_init(int opts)
{
	struct netbench_test_data *ret;
	ret = (__typeof__(ret)) malloc(sizeof(__typeof__(ret)));

	ret->type = NETBENCH_TEST_LATENCY;
	ret->u.latency = (struct netbench_test_latency *)
		malloc(sizeof(struct netbench_test_latency));

	return ret;
}

void netbench_test_latency_free(struct netbench_test_data *data)
{
	free(data->u.latency);
	free(data);
}

int netbench_test_latency_reset(struct netbench_test_data *data)
{
	return 0;
}

int netbench_test_latency_tester_run(
	int mrank,
	int trank,
	struct netbench_result *res,
	struct netbench_test_data *dat,
	unsigned int repeat,
	int opts
)
{
	int test;
	double start, stop;
	MPI_Status stat;
	struct netbench_result_latency *resptr;
	struct netbench_test_latency *datptr;

	resptr = res->u.latency;
	datptr = dat->u.latency;

	datptr->average = 1;
	test = 42;

	DEBUG(opts,"(%d) Send latency message %d to %d\n",mrank,test,trank);
	start = MPI_Wtime();
	MPI_Send(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	MPI_Recv(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
	stop = MPI_Wtime();
	
	resptr->latency = (stop - start);
	DEBUG(opts,"(%d) Latency of %d is %f\n",mrank,trank,resptr->latency);

	return 0;
}

int netbench_test_latency_tested_run(
	int mrank,
	int trank,
	struct netbench_test_data *dat,
	unsigned int repeat,
	int opts
)
{
	int test;
	struct netbench_test_latency *datptr;
	MPI_Status stat;

	datptr = dat->u.latency;

	datptr->average = 1;

	DEBUG(opts,"(%d) Waiting latency message from %d\n",mrank,trank);
	MPI_Recv(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
	DEBUG(opts,"(%d) Answer latency message from %d\n",mrank,trank);
	MPI_Send(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	
	return 0;
}
