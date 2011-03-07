#include <mpi.h>
#include <stdlib.h>
#include <sys/time.h>

#include "netbench_test_latency.h"
#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_result_latency.h"
#include "netbench_time.h"
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
	struct timeval start, stop, diff;
	MPI_Status stat;
	struct netbench_result_latency *resptr;
	struct netbench_test_latency *datptr;

	resptr = res->u.latency;
	datptr = dat->u.latency;

	datptr->average = 1;
	test = 42;

	gettimeofday(&start,NULL);

	MPI_Send(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	MPI_Recv(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);

	gettimeofday(&stop,NULL);

	timeval_subtract(&diff, &stop, &start);
	
	resptr->sec = diff.tv_sec;
	resptr->msec = ((float)diff.tv_usec)/1000;
	DEBUG(opts,"(%d) Latency of %d is %ds %.3fms\n",mrank,trank,resptr->sec,
		resptr->msec);

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

	MPI_Recv(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
	MPI_Send(&test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	DEBUG(opts,"(%d) Answer latency message from %d\n",mrank,trank);
	
	return 0;
}
