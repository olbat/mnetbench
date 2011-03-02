#ifndef _NETBENCH_RESULT_H
#define _NETBENCH_RESULT_H

#include "netbench_test_type.h"

#include "netbench_result_bandwidth.h"
#include "netbench_result_latency.h"

#define NETBENCH_RESULT_INFO_LIST \
{ \
	{ NETBENCH_TEST_BANDWIDTH, netbench_result_bandwidth_init, \
		netbench_result_bandwidth_free, \
		netbench_result_bandwidth_send, \
		netbench_result_bandwidth_recv, \
		netbench_result_bandwidth_print }, \
	{ NETBENCH_TEST_LATENCY, netbench_result_latency_init, \
		netbench_result_latency_free, \
		netbench_result_latency_send, \
		netbench_result_latency_recv, \
		netbench_result_latency_print }, \
	{ 0 } \
}



struct netbench_result_info
{
	enum netbench_test_type type;
	struct netbench_result *(*init_func)();
	void (*free_func)(struct netbench_result *res);
	int (*send_func)(struct netbench_result *res, int rank);
	struct netbench_result *(*recv_func)(int rank);
	void (*print_func)(struct netbench_result *res);
};

struct netbench_result
{
	enum netbench_test_type type;
	union netbench_result_union
	{
		struct netbench_result_bandwidth *bandwidth;
		struct netbench_result_latency *latency;
	} u;
	int srank;
	int drank;
};

struct netbench_result_info *netbench_result_info_fetch(enum netbench_test_type type);
struct netbench_result *netbench_result_init(enum netbench_test_type type,
	int srank, int drank);
void netbench_result_free(struct netbench_result *res);
int netbench_result_send(struct netbench_result *res, int rank);
struct netbench_result *netbench_result_recv(int rank);
void netbench_result_print(struct netbench_result *res);

#endif
