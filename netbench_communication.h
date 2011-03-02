#ifndef _NETBENCH_COMMUNICATION_H
#define _NETBENCH_COMMUNICATION_H

#include "netbench_communication_protocol.h"
#include "netbench_test_type.h"

void netbench_comm_error(char *msg);
void netbench_comm_proto_send(enum netbench_comm_proto proto, int rank);
void netbench_comm_proto_recv(enum netbench_comm_proto proto, int rank);

int netbench_comm_result_send(enum netbench_test_type type, int rank);
enum netbench_test_type netbench_comm_result_recv(int rank);

#endif
