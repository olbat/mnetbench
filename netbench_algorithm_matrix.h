#ifndef _NETBENCH_ALGORITHM_MATRIX_H
#define _NETBENCH_ALGORITHM_MATRIX_H

#include "netbench_role.h"
#include "linked_list.h"

void netbench_algo_matrix_run_client(struct linked_list *tasks,
	struct linked_list *results,int mrank,int tasknb);
void netbench_algo_matrix_run_master(struct linked_list *results, int tasknb);

#endif
