#include <mpi.h>

#include "netbench_master.h"
#include "options.h"
#include "debug.h"
#include "netbench_test_type.h"
#include "netbench_result.h"
#include "netbench_communication.h"


int netbench_master_run(int rank, int clientsnb, options_t opts)
{
	struct netbench_result *resptr;

	DEBUG(opts,"(m) Doing nothing%s\n","");
	while (1)
	{
		resptr = netbench_result_recv(1);
		
		netbench_result_print(resptr);

		netbench_result_free(resptr);
	}

	return 0;
}
