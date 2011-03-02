#include <mpi.h>

#include "netbench_master.h"
#include "options.h"
#include "debug.h"


int netbench_master_run(int rank, int clientsnb, options_t opts)
{
	int test = 42, i = clientsnb;

	DEBUG(opts,"(m) Doing nothing\n");
	sleep(8);

	return 0;
}
