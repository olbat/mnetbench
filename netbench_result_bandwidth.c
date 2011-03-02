#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "netbench_result_bandwidth.h"
#include "netbench_test_type.h"
#include "netbench_result.h"

struct netbench_result *
netbench_result_bandwidth_init()
{
	struct netbench_result *ret;
	ret = (struct netbench_result *) malloc(sizeof(struct netbench_result));

	ret->type = NETBENCH_TEST_BANDWIDTH;
	ret->u.bandwidth = (struct netbench_result_bandwidth *) 
		malloc(sizeof(struct netbench_result_bandwidth));

	ret->u.bandwidth->bw = 0;

	return ret;
}


void netbench_result_bandwidth_free(struct netbench_result *res)
{
	free(res->u.bandwidth);
	free(res);
}

int netbench_result_bandwidth_send(struct netbench_result *res, int rank)
{
	int bw;
	
	bw = res->u.bandwidth->bw;

	MPI_Send(&bw, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);

	return 0;
}

struct netbench_result *
netbench_result_bandwidth_recv(int rank)
{
	MPI_Status stat;
	struct netbench_result *ret;

	ret = netbench_result_bandwidth_init();
	
	MPI_Recv(&ret->u.bandwidth->bw, 1, MPI_INT, rank, 1, MPI_COMM_WORLD,
		&stat);

	return ret;
}

void netbench_result_bandwidth_print(struct netbench_result *res)
{
	fprintf(stdout,"(Bandwidth): \n\t bw=%d",res->u.bandwidth->bw);
}
