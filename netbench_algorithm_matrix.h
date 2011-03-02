#ifndef _NETBENCH_ALGORITHM_MATRIX_H
#define _NETBENCH_ALGORITHM_MATRIX_H

#include "netbench_role.h"
#include "linked_list.h"

void netbench_algo_matrix_run(enum netbench_role role, 
	struct linked_list *tasks,int mrank,int trank,int tasknb);

#endif
