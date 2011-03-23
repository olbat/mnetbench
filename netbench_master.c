#include <mpi.h>

#include "netbench_master.h"
#include "options.h"
#include "debug.h"
#include "netbench_test_type.h"
#include "netbench_list_result.h"
#include "netbench_communication.h"
#include "netbench_algorithm.h"
#include "netbench_algorithm_type.h"
#include "netbench_printer_type.h"
#include "netbench_printer.h"


int netbench_master_run(int rank, int clientsnb, options_t opts)
{
	int tmp;
	struct linked_list *results;
	struct linked_list *process;

	results = linked_list_init();
	process = linked_list_init();

	tmp = 0;

	while (tmp < clientsnb)
	{
		if (tmp == rank)
		{
			tmp++;
			continue;
		}

		linked_list_add(process,linked_list_proc_value_init(
			netbench_comm_proc_recv(tmp)
		));
		tmp++;
	}

	netbench_algo_run_master(NETBENCH_ALGO_MATRIX,results,clientsnb);

	netbench_printer_print(process, results, clientsnb,opts);

	linked_list_free(results);
	linked_list_free(process);

	return 0;
}
