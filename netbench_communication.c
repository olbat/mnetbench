#include <mpi.h>
#include <stdio.h>

#include "netbench_communication.h"
#include "netbench_communication_protocol.h"
#include "netbench_test_type.h"

void netbench_comm_error(char *msg)
{
	fprintf(stderr,"%s\n",msg);
}

void netbench_comm_proto_send(enum netbench_comm_proto proto, int rank)
{
	int prot;

	prot = proto;
	MPI_Send(&prot, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);
}

void netbench_comm_proto_recv(enum netbench_comm_proto proto, int rank)
{
	MPI_Status stat;
	int prot;

	MPI_Recv(&prot, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);
	if (prot != proto)
		netbench_comm_error("Protocol error");
}


int netbench_comm_result_send(enum netbench_test_type type, int rank)
{
	int typ;

	netbench_comm_proto_send(NETBENCH_COMM_PROTO_RESULT,rank);
	typ = type;
	MPI_Send(&typ, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);

	return 0;
}

enum netbench_test_type netbench_comm_result_recv(int rank)
{
	int ret;
	MPI_Status stat;

	netbench_comm_proto_recv(NETBENCH_COMM_PROTO_RESULT,rank);

	MPI_Recv(&ret, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);

	return ret;
}

