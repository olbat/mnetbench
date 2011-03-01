#include "netbench_algorithm_matrix.h"

#include "linked_list.h"
#include "netbench_task.h"
#include "netbench_list_task.h"
#include "netbench_role.h"

void netbench_algo_matrix_run(
	enum netbench_role role,
	int mrank,
	int trank,
	int tasknb,
	int opts
)
{
	struct linked_list *results;
	struct linked_list *tasks;
	struct netbench_task *tmptask;

	if (role == NETBENCH_ROLE_TESTER)
		results = linked_list_init();
	else
		results = 0;

	tasks = linked_list_init();
	tmptask = netbench_task_init(NETBENCH_TEST_BANDWIDTH,results,3,0);

	linked_list_add(tasks,linked_list_task_value_init(tmptask));

	netbench_list_task_run(tasks,role,mrank,trank);

	linked_list_free(tasks);
	linked_list_free(results);

	
	
}
