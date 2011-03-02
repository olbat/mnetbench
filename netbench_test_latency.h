#ifndef _NETBENCH_TEST_LATENCY_H
#define _NETBENCH_TEST_LATENCY_H

#include "netbench_test.h"
#include "netbench_result.h"


struct netbench_test_latency
{
	double average;
};

struct netbench_test_data *netbench_test_latency_init(int opts);
void netbench_test_latency_free(struct netbench_test_data *data);
int netbench_test_latency_reset(struct netbench_test_data *data);
int netbench_test_latency_tester_run(int mrank, int trank, struct netbench_result *res,struct netbench_test_data *dat, unsigned int repeat, int opts);
int netbench_test_latency_tested_run(int mrank, int trank,struct netbench_test_data *dat, unsigned int repeat, int opts);

#endif
