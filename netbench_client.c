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
#include "netbench_communication.h"
#include "netbench_list_result.h"

int netbench_client_run(int mrank, int clientsnb, options_t opts)
{
	struct linked_list *results;
	struct linked_list *tasks;
	struct netbench_task *tmptask;

	results = linked_list_init();

	tasks = linked_list_init();

	tmptask = netbench_task_init(NETBENCH_TEST_BANDWIDTH,results,1,opts);
	linked_list_add(tasks,linked_list_task_value_init(tmptask));

	tmptask = netbench_task_init(NETBENCH_TEST_LATENCY,results,2,opts);
	linked_list_add(tasks,linked_list_task_value_init(tmptask));

	netbench_algo_run_client(NETBENCH_ALGO_MATRIX,tasks,results,mrank,
		clientsnb);

	linked_list_free(tasks);
	linked_list_free(results);

	return 0;
}
