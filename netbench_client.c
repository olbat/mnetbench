#include <mpi.h>
#include <stdio.h>

#include "netbench_client.h"
#include "options.h"
#include "debug.h"
#include "mnetbench.h"
#include "linked_list.h"
#include "netbench_task.h"
#include "netbench_role.h"
#include "netbench_algorithm.h"
#include "netbench_algorithm_type.h"

int netbench_client_run(int mrank, int clientsnb, options_t opts)
{
	int test, trank;
	struct linked_list *results;
	struct linked_list *tasks;
	struct netbench_task *tmptask;
	enum netbench_role role;
	MPI_Status stat;

	if (mrank == 1)
	{
		role = NETBENCH_ROLE_TESTER;
		trank = -1;
	}
	else
	{
		role = NETBENCH_ROLE_TESTED;
		trank = 1;
	}
	
	if (role == NETBENCH_ROLE_TESTER)
		results = linked_list_init();
	else
		results = 0;

	tasks = linked_list_init();
	tmptask = netbench_task_init(NETBENCH_TEST_BANDWIDTH,results,3,opts);

	linked_list_add(tasks,linked_list_task_value_init(tmptask));

	netbench_algo_run(NETBENCH_ALGO_MATRIX,role,tasks,mrank,trank,clientsnb);
	
	linked_list_free(tasks);
	linked_list_free(results);

	return 0;
}
