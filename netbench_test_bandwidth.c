#include <mpi.h>
#include <stdlib.h>

#include "netbench_test_bandwidth.h"
#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_result_bandwidth.h"


struct netbench_test_data *
netbench_test_bandwidth_init(int opts)
{
	struct netbench_test_data *ret;
	ret = (__typeof__(ret)) malloc(sizeof(__typeof__(ret)));

	ret->type = NETBENCH_TEST_BANDWIDTH;
	ret->u.bandwidth = (struct netbench_test_bandwidth *)
		malloc(sizeof(struct netbench_test_bandwidth));

	ret->u.bandwidth = 0;

	return ret;
}

void netbench_test_bandwidth_free(struct netbench_test_data *data)
{
	free(data->u.bandwidth);
	free(data);
}

int netbench_test_bandwidth_reset(struct netbench_test_data *data)
{
	return 0;
}

int netbench_test_bandwidth_tester_run(
	int mrank,
	int trank,
	struct netbench_result *res,
	struct netbench_test_data *dat,
	unsigned int repeat,
	int opts
)
{
	struct netbench_result_bandwidth *resptr;
	resptr = res->u.bandwidth;
	struct netbench_test_bandwidth *datptr;
	datptr = dat->u.bandwidth;

	datptr->average = 1;
	resptr->bw = 1;
	
	return 0;
}

int netbench_test_bandwidth_tested_run(
	int mrank,
	int trank,
	struct netbench_test_data *dat,
	unsigned int repeat,
	int opts
)
{
	struct netbench_test_bandwidth *datptr;
	datptr = dat->u.bandwidth;

	datptr->average = 1;
	
	return 0;
}
