#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#include "netbench_result.h"
#include "netbench_test_type.h"
#include "netbench_communication.h"

#include "netbench_result_bandwidth.h"
#include "netbench_result_latency.h"

#include "netbench_printer_type.h"


__inline__ struct netbench_result_info *
netbench_result_info_fetch(enum netbench_test_type type)
{
	static struct netbench_result_info resultinfolist[] = 
		NETBENCH_RESULT_INFO_LIST;
	struct netbench_result_info *ptr;

	ptr = resultinfolist;

	while ((ptr->type != NETBENCH_TEST_NONE) && (ptr->type != type))
		ptr++;
	
	return ptr;
}

struct netbench_result *
netbench_result_init(enum netbench_test_type type, int srank, int drank)
{
	struct netbench_result *ret;
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(type);
	if (!info)
		return 0;

	ret = info->init_func();
	ret->srank = srank;
	ret->drank = drank;

	return ret;
}

void
netbench_result_free(struct netbench_result *res)
{
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(res->type);
	if (!info)
		return;

	info->free_func(res);
}

int netbench_result_send(struct netbench_result *res, int rank)
{
	int srank,drank;
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(res->type);
	if (!info)
		return 1;

	netbench_comm_result_send(res->type,rank);
	
	srank = res->srank;
	MPI_Send(&srank, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);
	drank = res->drank;
	MPI_Send(&drank, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);

	return info->send_func(res,rank);
}

struct netbench_result *
netbench_result_recv(int rank)
{
	struct netbench_result *ret;
	int srank,drank;
	MPI_Status stat;
	enum netbench_test_type type;
	struct netbench_result_info *info;

	type = netbench_comm_result_recv(rank);

	info = netbench_result_info_fetch(type);
	if (!info)
		return 0;

	MPI_Recv(&srank, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);
	MPI_Recv(&drank, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);

	ret = info->recv_func(rank);
	ret->srank = srank;
	ret->drank = drank;

	return ret;
}

void netbench_result_print(
	enum netbench_printer_type prtype,
	struct netbench_result *res
)
{
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(res->type);
	if (!info)
		return ;

	switch (prtype)
	{
	case NETBENCH_PRINTER_CLASSIC:
		fprintf(stdout,"[%d -> %d] %s test results:\n",
			res->srank,res->drank,netbench_test_type_name(res->type));
		break;
	default:
		break;
	}

	info->print_func(prtype,res);

	switch (prtype)
	{
	case NETBENCH_PRINTER_CLASSIC:
		fprintf(stdout,"\n");
		break;
	default:
		break;
	}
}
