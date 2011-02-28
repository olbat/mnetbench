#include <stdlib.h>

#include "netbench_test.h"
#include "netbench_test_type.h"
#include "netbench_result.h"

#include "netbench_test_bandwidth.h"


__inline__ struct netbench_test_info *
netbench_test_info_fetch(enum netbench_test_type type)
{
	struct netbench_test_info *ptr;
	struct netbench_test_info testinfolist[] = {
		{ NETBENCH_TEST_BANDWIDTH,
			netbench_test_bandwidth_init,
			netbench_test_bandwidth_free,
			netbench_test_bandwidth_reset,
			netbench_test_bandwidth_run
		},
		{ 0 }
	};

	ptr = testinfolist;

	while ((ptr) && (ptr->type != type))
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
netbench_test_run(
	struct netbench_test *test,
	struct netbench_result *res,
	int mrank,
	int trank,
	unsigned int repeat
)
{
	unsigned int i;
	struct netbench_test_info *info;
	info = netbench_test_info_fetch(test->type);
	if (!info)
		return 1;

	i = repeat;
	while (i--)
		info->test_func(mrank,trank,res,test->data,repeat,test->opts);

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
