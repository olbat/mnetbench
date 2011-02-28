#include <stdlib.h>

#include "netbench_result_bandwidth.h"
#include "netbench_test_type.h"
#include "netbench_result.h"

struct netbench_result *
netbench_result_bandwidth_init()
{
	struct netbench_result *ret;
	ret = (struct netbench_result *) malloc(sizeof(struct netbench_result));

	ret->type = NETBENCH_TEST_BANDWIDTH;
	ret->u.bandwidth = (struct netbench_result_bandwidth *) 
		malloc(sizeof(struct netbench_result_bandwidth));

	ret->u.bandwidth->bw = 0;

	return ret;
}


void
netbench_result_bandwidth_free(struct netbench_result *res)
{
	free(res->u.bandwidth);
	free(res);
}
