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
#include "netbench_list_task.h"

int netbench_client_run(int mrank, int clientsnb, options_t opts)
{
	struct linked_list *results;
	struct linked_list *tasks;

	results = linked_list_init();

	tasks = linked_list_init();

	netbench_list_task_init(tasks,results,opts);

	netbench_algo_run_client(NETBENCH_ALGO_MATRIX,tasks,results,mrank,
		clientsnb);

	linked_list_free(tasks);
	linked_list_free(results);

	return 0;
}
