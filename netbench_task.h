#ifndef _NETBENCH_TASK_H
#define _NETBENCH_TASK_H

#include "netbench_test_type.h"
#include "netbench_result.h"
#include "linked_list.h"
#include "netbench_role.h"

struct netbench_task
{
	enum netbench_test_type type;
	unsigned int repeat;
	struct netbench_test *test;
	struct linked_list *list_result;
};

struct netbench_task *netbench_task_init(enum netbench_test_type type, struct linked_list *res, unsigned int repeat, int opts);
void netbench_task_free(struct netbench_task *task);
void netbench_task_run(struct netbench_task *task, enum netbench_role role,
	int srank, int drank);

#endif
