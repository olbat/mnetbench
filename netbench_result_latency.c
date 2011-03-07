#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "netbench_result_latency.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_printer_type.h"

struct netbench_result *
netbench_result_latency_init()
{
	struct netbench_result *ret;
	ret = (struct netbench_result *) malloc(sizeof(struct netbench_result));

	ret->type = NETBENCH_TEST_LATENCY;
	ret->u.latency = (struct netbench_result_latency *) 
		malloc(sizeof(struct netbench_result_latency));

	ret->u.latency->sec = 0;
	ret->u.latency->msec = 0.0f;

	return ret;
}


void netbench_result_latency_free(struct netbench_result *res)
{
	free(res->u.latency);
	free(res);
}

int netbench_result_latency_send(struct netbench_result *res, int rank)
{
	int lats;
	float latm;
	
	lats = res->u.latency->sec;
	latm = res->u.latency->msec;

	MPI_Send(&lats, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);
	MPI_Send(&latm, 1, MPI_FLOAT, rank, 1, MPI_COMM_WORLD);

	return 0;
}

struct netbench_result *
netbench_result_latency_recv(int rank)
{
	MPI_Status stat;
	struct netbench_result *ret;

	ret = netbench_result_latency_init();
	
	MPI_Recv(&ret->u.latency->sec, 1, MPI_INT, rank, 1, MPI_COMM_WORLD,
		&stat);
	MPI_Recv(&ret->u.latency->msec, 1, MPI_FLOAT, rank, 1, MPI_COMM_WORLD,
		&stat);

	return ret;
}

void netbench_result_latency_print(
	enum netbench_printer_type prtype,
	struct netbench_result *res
)
{
	switch (prtype)
	{
	case NETBENCH_PRINTER_CLASSIC:
		fprintf(stdout,"\tsec=%ds\n",res->u.latency->sec);
		fprintf(stdout,"\tmsec=%.3fms",res->u.latency->msec);
		break;
	case NETBENCH_PRINTER_HTML:
	default:
		fprintf(stdout,"%ds %.3fms",res->u.latency->sec,
			res->u.latency->msec);
		break;
	}
}
