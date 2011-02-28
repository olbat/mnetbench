#ifndef _NETBENCH_TASK_H
#define _NETBENCH_TASK_H

#include "netbench_test.h"
#include "netbench_result.h"

struct netbench_task
{
	unsigned int repeat;
	struct netbench_test *test;
	struct netbench_result *res;
};

struct netbench_task *netbench_task_init(enum netbench_test_type, unsigned int repeat);

#endif
