#ifndef _NETBENCH_TEST_LATENCY_H
#define _NETBENCH_TEST_LATENCY_H


struct netbench_result_latency
{
	double latency;
};

int netbench_test_latency(int mrank, int trank, struct netbench_result *res);

#endif

