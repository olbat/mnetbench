#include <mpi.h>
#include <stdio.h>
#include <string.h>

#include "netbench_communication.h"
#include "netbench_communication_protocol.h"
#include "netbench_test_type.h"
#include "netbench_role.h"

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

int netbench_comm_list_send(unsigned int size, int rank)
{
	netbench_comm_proto_send(NETBENCH_COMM_PROTO_LIST,rank);
	MPI_Send(&size, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);

	return 0;
}

unsigned int netbench_comm_list_recv(int rank)
{
	unsigned int ret;
	MPI_Status stat;

	netbench_comm_proto_recv(NETBENCH_COMM_PROTO_LIST,rank);

	MPI_Recv(&ret, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);

	return ret;
}

int netbench_comm_role_send(enum netbench_role role, int rank)
{
	int rol;

	netbench_comm_proto_send(NETBENCH_COMM_PROTO_ROLE,rank);
	rol = role;
	MPI_Send(&rol, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);

	return 0;
}

enum netbench_role netbench_comm_role_recv(int rank)
{
	int ret;
	MPI_Status stat;

	netbench_comm_proto_recv(NETBENCH_COMM_PROTO_ROLE,rank);

	MPI_Recv(&ret, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);

	return ret;
}

int netbench_comm_rank_send(int ranktosend, int rank)
{
	int rts;

	netbench_comm_proto_send(NETBENCH_COMM_PROTO_RANK,rank);
	rts = ranktosend;
	MPI_Send(&rts, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);

	return 0;
}

int netbench_comm_rank_recv(int rank)
{
	int ret;
	MPI_Status stat;

	netbench_comm_proto_recv(NETBENCH_COMM_PROTO_RANK,rank);

	MPI_Recv(&ret, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);

	return ret;
}

int netbench_comm_proc_send(struct netbench_process *proc, int rank)
{
	int num, size;
	char *name;

	netbench_comm_proto_send(NETBENCH_COMM_PROTO_PROC,rank);
	num = proc->num;
	MPI_Send(&num, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);
	size = strlen(proc->name) + 1;
	MPI_Send(&size, 1, MPI_INT, rank, 1, MPI_COMM_WORLD);
	name = proc->name;
	MPI_Send(name, size, MPI_CHAR, rank, 1, MPI_COMM_WORLD);

	return 0;
}

struct netbench_process *netbench_comm_proc_recv(int rank)
{
	struct netbench_process *ret;
	static char name[MPI_MAX_PROCESSOR_NAME];
	int num,size;
	MPI_Status stat;

	netbench_comm_proto_recv(NETBENCH_COMM_PROTO_PROC,rank);
	MPI_Recv(&num, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);
	MPI_Recv(&size, 1, MPI_INT, rank, 1, MPI_COMM_WORLD, &stat);
	MPI_Recv(name, size, MPI_CHAR, rank, 1, MPI_COMM_WORLD, &stat);

	ret = netbench_process_init(num,name);

	return ret;
}
