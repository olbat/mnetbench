#include <mpi.h>
#include <stdlib.h>
#include <sys/time.h>

#include "netbench_test_bandwidth.h"
#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_result_bandwidth.h"
#include "netbench_time.h"
#include "netbench_printer_tool.h"
#include "debug.h"


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
	unsigned int buffsize = NETBENCH_TEST_BANDWIDTH_DEFAULT_PACKET_SIZE,
		size, elapsedsec;
	unsigned long long count;
	char buff[buffsize];
	char printbuff[NETBENCH_PRINTER_BUFF_SIZE];
	struct timeval start, stop, cur, diff;
	MPI_Datatype bwtype;
	struct netbench_result_bandwidth *resptr;
	resptr = res->u.bandwidth;
	struct netbench_test_bandwidth *datptr;
	datptr = dat->u.bandwidth;
	datptr->average = 1;

	MPI_Type_contiguous(buffsize, MPI_CHAR, &bwtype);
	MPI_Type_commit(&bwtype);

	count = 0;
	size = 1;
	elapsedsec = 0;
	
	gettimeofday(&start,NULL);
	gettimeofday(&cur,NULL);
	timeval_subtract(&diff, &cur, &start);
	while (diff.tv_sec < NETBENCH_TEST_BANDWIDTH_DEFAULT_TIME)
	{
		MPI_Send(&size, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
		MPI_Send(&buff, size, bwtype, trank, 1, MPI_COMM_WORLD);

		gettimeofday(&cur,NULL);
		timeval_subtract(&diff, &cur, &start);
		count += size;
	}
	gettimeofday(&stop,NULL);
	timeval_subtract(&diff, &stop, &start);
	size = 0;
	MPI_Send(&size, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	resptr->bw = ((double) 
			(count * NETBENCH_TEST_BANDWIDTH_DEFAULT_PACKET_SIZE)
		) / diff.tv_sec;

	DEBUG(opts,"(%d) Bandwidth of %d is %s\n",mrank,trank,
		netbench_printer_tool_bandwidth(
			printbuff,sizeof(printbuff),resptr->bw
		)
	);
	
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
	unsigned int buffsize = NETBENCH_TEST_BANDWIDTH_DEFAULT_PACKET_SIZE,
		size;
	char buff[buffsize];
	MPI_Datatype bwtype;
	struct netbench_test_bandwidth *datptr;
	MPI_Status stat;
	datptr = dat->u.bandwidth;
	datptr->average = 1;

	MPI_Type_contiguous(buffsize, MPI_CHAR, &bwtype);
	MPI_Type_commit(&bwtype);

	while (1)
	{
		MPI_Recv(&size, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
		if (!size)
			break;
		MPI_Recv(&buff, size, bwtype, trank, 1, MPI_COMM_WORLD, &stat);
	}

	DEBUG(opts,"(%d) Done Bandwidth test from %d\n",mrank,trank);
	
	return 0;
}
