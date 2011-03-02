#ifndef _NETBENCH_RESULT_BANDWIDTH_H
#define _NETBENCH_RESULT_BANDWIDTH_H

struct netbench_result_bandwidth
{
	int bw;
};

struct netbench_result *netbench_result_bandwidth_init();
void netbench_result_bandwidth_free(struct netbench_result *res);
int netbench_result_bandwidth_send(struct netbench_result *res, int rank);
struct netbench_result *netbench_result_bandwidth_recv(int rank);
void netbench_result_bandwidth_print(struct netbench_result *res);

#endif
