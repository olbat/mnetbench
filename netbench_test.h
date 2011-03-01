#ifndef _NETBENCH_TEST_H
#define _NETBENCH_TEST_H

#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_role.h"

#define NETBENCH_TEST_INFO_LIST \
{ \
	{ NETBENCH_TEST_BANDWIDTH, netbench_test_bandwidth_init, \
		netbench_test_bandwidth_free, netbench_test_bandwidth_reset, \
		netbench_test_bandwidth_tester_run, \
		netbench_test_bandwidth_tested_run }, \
	{ 0 } \
}



struct netbench_test_info
{
	enum netbench_test_type type;
	struct netbench_test_data *(*init_func)(int opts);
	void (*free_func)(struct netbench_test_data *test);
	int (*reset_func)(struct netbench_test_data *test);
	int (*tester_func)(int myrank, int tarrank, struct netbench_result *res,
		struct netbench_test_data *dat, unsigned int repeat, int opts);
	int (*tested_func)(int myrank, int tarrank,
		struct netbench_test_data *dat, unsigned int repeat, int opts);
};

struct netbench_test
{
	enum netbench_test_type type;
	struct netbench_test_data *data;
	int opts;
	/* void (*print_func)(struct netbench_result *res); */
};

struct netbench_test_data
{
	enum netbench_test_type type;
	union netbench_test_data_union
	{
		struct netbench_test_latency *latency;
		struct netbench_test_bandwidth *bandwidth;
	} u;
};

struct netbench_test *netbench_test_init(
	enum netbench_test_type type, unsigned int repeat, int opts);
void netbench_test_free(struct netbench_test *test);
int netbench_test_reset(struct netbench_test *test);
int netbench_test_run_tester(struct netbench_test *test,
	struct netbench_result *res,int myrank,int tarrank,unsigned int repeat);
int netbench_test_run_tested(struct netbench_test *test,int myrank,int tarrank,
	unsigned int repeat);

#endif
