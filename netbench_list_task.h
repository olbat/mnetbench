#ifndef _NETBENCH_LIST_TASK_H
#define _NETBENCH_LIST_TASK_H

#include "linked_list.h"

void netbench_list_task_run(struct linked_list *tasks,enum netbench_role role,
	int mrank, int trank);

#endif
