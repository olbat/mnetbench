#ifndef _NETBENCH_COMMUNICATION_H
#define _NETBENCH_COMMUNICATION_H

#include "netbench_communication_protocol.h"
#include "netbench_test_type.h"
#include "netbench_role.h"

void netbench_comm_error(char *msg);
void netbench_comm_proto_send(enum netbench_comm_proto proto, int rank);
void netbench_comm_proto_recv(enum netbench_comm_proto proto, int rank);

int netbench_comm_result_send(enum netbench_test_type type, int rank);
enum netbench_test_type netbench_comm_result_recv(int rank);
int netbench_comm_list_send(unsigned int size, int rank);
unsigned int netbench_comm_list_recv(int rank);
int netbench_comm_role_send(enum netbench_role type, int rank);
enum netbench_role netbench_comm_role_recv(int rank);
int netbench_comm_rank_send(int ranktosend, int rank);
int netbench_comm_rank_recv(int rank);

#endif
