#ifndef _NETBENCH_TASK_H
#define _NETBENCH_TASK_H

struct netbench_task
{
	unsigned int repeat;
	int (*netbench_test_func)(struct netbench_result *res);
};

#endif
