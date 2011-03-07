#ifndef _NETBENCH_RESULT_LATENCY_H
#define _NETBENCH_RESULT_LATENCY_H

struct netbench_result_latency
{
	int sec;
	float msec;
};

struct netbench_result *netbench_result_latency_init();
void netbench_result_latency_free(struct netbench_result *res);
int netbench_result_latency_send(struct netbench_result *res, int rank);
struct netbench_result *netbench_result_latency_recv(int rank);
void netbench_result_latency_print(struct netbench_result *res);

#endif
