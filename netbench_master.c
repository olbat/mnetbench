#include <mpi.h>

#include "netbench_master.h"
#include "options.h"
#include "debug.h"
#include "netbench_test_type.h"
#include "netbench_list_result.h"
#include "netbench_communication.h"
#include "netbench_algorithm.h"
#include "netbench_algorithm_type.h"


int netbench_master_run(int rank, int clientsnb, options_t opts)
{
	struct linked_list *results;

	results = linked_list_init();

	netbench_algo_run_master(NETBENCH_ALGO_MATRIX,results,clientsnb);

	netbench_list_result_print(results);

	linked_list_free(results);

	return 0;
}
