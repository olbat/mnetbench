#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "mnetbench.h"
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

	ret->u.bandwidth->time = NETBENCH_TEST_BANDWIDTH_DEFAULT_TIME;
	ret->u.bandwidth->packet_size =
		NETBENCH_TEST_BANDWIDTH_DEFAULT_PACKET_SIZE;

	netbench_test_bandwidth_parse_options(ret);

	ret->u.bandwidth->packet_buff = (char *) 
		malloc(sizeof(char)*ret->u.bandwidth->packet_size);
	

	return ret;
}

__inline__ int
netbench_test_bandwidth_parse_options(struct netbench_test_data *dat)
{
	char namebuff[OPT_TEST_BUFF_SIZE],
		valbuff[OPT_TEST_BUFF_SIZE];
	char *ptr;

	ptr = opt_test_args.bandwidth;
	while ((ptr) && (*ptr))
	{
		ptr = opt_test_parse_option(namebuff,valbuff, ptr);
		if (!strcmp("packet_size",namebuff))
			dat->u.bandwidth->packet_size = strtoll(valbuff,NULL,10);
		else if (!strcmp("time",namebuff))
			dat->u.bandwidth->time = strtol(valbuff,NULL,10);
		else
		{
			fprintf(stderr,"(%s) Unknown option \"%s\"\n",
				netbench_test_type_name(NETBENCH_TEST_BANDWIDTH),
				namebuff);
		}
	}
	return 0;
}

void netbench_test_bandwidth_free(struct netbench_test_data *data)
{
	free(data->u.bandwidth->packet_buff);
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
	static char printbuff[NETBENCH_PRINTER_BUFF_SIZE];
	unsigned int size, elapsedsec;
	unsigned long long count;
	struct timeval start, stop, cur, diff;
	MPI_Datatype bwtype;

	struct netbench_result_bandwidth *resptr;
	resptr = res->u.bandwidth;
	struct netbench_test_bandwidth *datptr;
	datptr = dat->u.bandwidth;

	MPI_Type_contiguous(datptr->packet_size, MPI_CHAR, &bwtype);
	MPI_Type_commit(&bwtype);

	count = 0;
	size = 1;
	elapsedsec = 0;
	
	gettimeofday(&start,NULL);
	gettimeofday(&cur,NULL);
	timeval_subtract(&diff, &cur, &start);
	while (diff.tv_sec < datptr->time)
	{
		MPI_Send(&size, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
		MPI_Send(datptr->packet_buff, size, bwtype, trank, 1,
			MPI_COMM_WORLD);

		gettimeofday(&cur,NULL);
		timeval_subtract(&diff, &cur, &start);
		count += size;
	}
	gettimeofday(&stop,NULL);
	timeval_subtract(&diff, &stop, &start);

	size = 0;
	MPI_Send(&size, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);

	resptr->bw = ((double) (count * datptr->packet_size)) 
		/ (diff.tv_sec + (diff.tv_usec * 10e-6));

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
	unsigned int size;
	MPI_Datatype bwtype;
	struct netbench_test_bandwidth *datptr;
	MPI_Status stat;
	datptr = dat->u.bandwidth;

	MPI_Type_contiguous(datptr->packet_size, MPI_CHAR, &bwtype);
	MPI_Type_commit(&bwtype);

	while (1)
	{
		MPI_Recv(&size, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
		if (!size)
			break;
		MPI_Recv(datptr->packet_buff, size, bwtype, trank, 1,
			MPI_COMM_WORLD, &stat);
	}

	DEBUG(opts,"(%d) Done Bandwidth test from %d\n",mrank,trank);
	
	return 0;
}
