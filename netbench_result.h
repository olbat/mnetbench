#ifndef _NETBENCH_RESULT_H
#define _NETBENCH_RESULT_H

#include "netbench_test_type.h"


struct netbench_result_info
{
	enum netbench_test_type type;
	struct netbench_result *(*init_func)();
	void (*free_func)(struct netbench_result *res);
	int (*send_func)(struct netbench_result *res, int rank);
	struct netbench_result *(*recv_func)(int rank);
};

struct netbench_result
{
	enum netbench_test_type type;
	union netbench_result_union
	{
		struct netbench_result_bandwidth *bandwidth;
	} u;
};

struct netbench_result_info *netbench_result_info_fetch(enum netbench_test_type type);
struct netbench_result *netbench_result_init(enum netbench_test_type type);
void netbench_result_free(struct netbench_result *res);
int netbench_result_send(struct netbench_result *res, int rank);
struct netbench_result *netbench_result_recv(struct netbench_result *res, int rank);

#endif
