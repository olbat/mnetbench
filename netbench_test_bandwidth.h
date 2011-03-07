#ifndef _NETBENCH_TEST_BANDWIDTH_H
#define _NETBENCH_TEST_BANDWIDTH_H

#include "netbench_test.h"
#include "netbench_result.h"

#define NETBENCH_TEST_BANDWIDTH_DEFAULT_TIME 2 /* seconds */
#define NETBENCH_TEST_BANDWIDTH_DEFAULT_PACKET_SIZE 512*1024 /* Bytes */


struct netbench_test_bandwidth
{
	double average;
};

struct netbench_test_data *netbench_test_bandwidth_init(int opts);
void netbench_test_bandwidth_free(struct netbench_test_data *data);
int netbench_test_bandwidth_reset(struct netbench_test_data *data);
int netbench_test_bandwidth_tester_run(int mrank, int trank, struct netbench_result *res,struct netbench_test_data *dat, unsigned int repeat, int opts);
int netbench_test_bandwidth_tested_run(int mrank, int trank,struct netbench_test_data *dat, unsigned int repeat, int opts);

#endif
