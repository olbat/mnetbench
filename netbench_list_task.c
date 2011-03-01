#include "netbench_list_task.h"
#include "netbench_task.h"
#include "linked_list.h"

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
