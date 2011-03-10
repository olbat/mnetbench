#include <stdlib.h>
#include <mpi.h>

#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_role.h"

#include "netbench_test_bandwidth.h"
#include "netbench_test_latency.h"


struct netbench_test_info *
netbench_test_info_fetch(enum netbench_test_type type)
{
	static struct netbench_test_info testinfolist[] = 
		NETBENCH_TEST_INFO_LIST;
	struct netbench_test_info *ptr;

	ptr = testinfolist;

	while ((ptr->type != NETBENCH_TEST_NONE) && (ptr->type != type))
		ptr++;
	
	return ptr;
}

__inline__ struct netbench_test *
netbench_test_init(enum netbench_test_type type, unsigned int repeat, int opts)
{
	struct netbench_test *ret;
	struct netbench_test_info *info;
	info = netbench_test_info_fetch(type);
	if (!info)
		return 0;

	ret = (__typeof__(ret)) malloc(sizeof(struct netbench_test_data));

	ret->type = type;
	ret->data = info->init_func(opts);
	ret->opts = opts;
	
	return ret;
}

__inline__ void 
netbench_test_free(struct netbench_test *test)
{
	struct netbench_test_info *info;
	info = netbench_test_info_fetch(test->type);
	if (!info)
		return;

	info->free_func(test->data);
	free(test);
}

__inline__ int
netbench_test_run_tester(
	struct netbench_test *test,
	struct netbench_result *res,
	int mrank,
	int trank,
	unsigned int repeat
)
{
	unsigned int i;
	int init_test;
	MPI_Status stat;
	struct netbench_test_info *info;
	info = netbench_test_info_fetch(test->type);
	if (!info)
		return 1;

	/* For some strange reasons, we need to make a first fake connection
	 * in order to get good test results (the first time a connection is 
	 * made between two process, packets are routed weirdly
	 */
	init_test = 0;
	MPI_Send(&init_test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);
	MPI_Recv(&init_test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);

	i = repeat;
	while (i--)
		info->tester_func(mrank,trank,res,test->data,repeat,test->opts);

	return 0;
}

__inline__ int
netbench_test_run_tested(
	struct netbench_test *test,
	int mrank,
	int trank,
	unsigned int repeat
)
{
	unsigned int i;
	int init_test;
	MPI_Status stat;
	struct netbench_test_info *info;
	info = netbench_test_info_fetch(test->type);
	if (!info)
		return 1;

	/* For some strange reasons, we need to make a first fake connection
	 * in order to get good test results (the first time a connection is 
	 * made between two process, packets are routed weirdly
	 */
	MPI_Recv(&init_test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD, &stat);
	MPI_Send(&init_test, 1, MPI_INT, trank, 1, MPI_COMM_WORLD);

	i = repeat;
	while (i--)
		info->tested_func(mrank,trank,test->data,repeat,test->opts);

	return 0;
}

__inline__ int
netbench_test_reset(struct netbench_test *test)
{
	struct netbench_test_info *info;
	info = netbench_test_info_fetch(test->type);
	if (!info)
		return 1;

	return info->reset_func(test->data);
}
