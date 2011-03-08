#include <stdlib.h>

#include "netbench_task.h"
#include "netbench_test_type.h"
#include "netbench_test.h"
#include "linked_list.h"
#include "netbench_test.h"


struct netbench_task *
netbench_task_init(
	enum netbench_test_type type, 
	struct linked_list *results,
	unsigned int repeat,
	int opts
)
{
	struct netbench_task *ret;
	ret = (struct netbench_task *) malloc(sizeof(struct netbench_task));

	ret->type = type;
	ret->repeat = repeat;
	ret->test = netbench_test_init(type,repeat,opts);
	ret->list_result = results;

	return ret;
}

void netbench_task_free(struct netbench_task *task)
{
	netbench_test_free(task->test);
	free(task);
}

void netbench_task_run(
	struct netbench_task *task,
	enum netbench_role role,
	int mrank,
	int trank
)
{
	if (role == NETBENCH_ROLE_TESTER)
	{
		struct netbench_result *res;
		res = netbench_result_init(task->type,mrank,trank);

		linked_list_add(task->list_result,
			linked_list_res_value_init(res));
		netbench_test_run_tester(task->test,res,mrank,trank,
			task->repeat);
	}
	else
	{
		netbench_test_run_tested(task->test,mrank,trank,task->repeat);
	}
}
