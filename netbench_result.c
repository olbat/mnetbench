#include <stdlib.h>

#include "netbench_result.h"
#include "netbench_test_type.h"

#include "netbench_result_bandwidth.h"


__inline__ struct netbench_result_info *
netbench_result_info_fetch(enum netbench_test_type type)
{
	struct netbench_result_info *ptr;
	struct netbench_result_info resultinfolist[] = {
		{ NETBENCH_TEST_BANDWIDTH,
			netbench_result_bandwidth_init,
			netbench_result_bandwidth_free,
			0,0
		},
		{ 0 }
	};

	ptr = resultinfolist;

	while ((ptr) && (ptr->type != type))
		ptr++;
	
	return ptr;
}

struct netbench_result *
netbench_result_init(enum netbench_test_type type)
{
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(type);
	if (!info)
		return 0;

	return info->init_func();
}

void
netbench_result_free(struct netbench_result *res)
{
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(res->type);
	if (!info)
		return;

	info->free_func(res);
}

int netbench_result_send(struct netbench_result *res, int rank)
{
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(res->type);
	if (!info)
		return 1;

	return info->send_func(res,rank);
}

struct netbench_result *
netbench_result_recv(struct netbench_result *res, int rank)
{
	struct netbench_result_info *info;
	info = netbench_result_info_fetch(res->type);
	if (!info)
		return 0;

	return info->recv_func(rank);
}
