#include "netbench_list_task.h"
#include "netbench_task.h"
#include "linked_list.h"
#include "netbench_test.h"
#include "options.h"

__inline__ struct linked_list *
netbench_list_task_init(
	struct linked_list *tasks,
	struct linked_list *results,
	options_t opts
)
{
	static struct netbench_test_info testinfolist[] =
		NETBENCH_TEST_INFO_LIST;
	struct netbench_test_info *ptr;

	ptr = testinfolist;

	while (ptr->type != NETBENCH_TEST_NONE)
	{
		if (OPT_GET(opts,ptr->optflag))
		{
			linked_list_add(tasks,linked_list_task_value_init(
				netbench_task_init(ptr->type,results,1,opts)
			));
		}
		ptr++;
	}

	return tasks;
}

void netbench_list_task_run(
	struct linked_list *tasks,
	enum netbench_role role,
	int mrank,
	int trank
)
{
	while (tasks)
	{
		netbench_task_run(tasks->value->u.task,role,mrank,trank);
		tasks = tasks->next;
	}
}
