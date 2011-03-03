#ifndef _NETBENCH_ALGORITHM_H
#define _NETBENCH_ALGORITHM_H

#include "netbench_algorithm_type.h"
#include "netbench_role.h"
#include "linked_list.h"

#include "netbench_algorithm_matrix.h"

#define NETBENCH_ALGO_INFO_LIST \
{ \
	{ NETBENCH_ALGO_MATRIX,netbench_algo_matrix_run_master, \
		netbench_algo_matrix_run_client }, \
	{ 0 } \
}

struct netbench_algo_info
{
	enum netbench_algo_type type;
	void (*func_run_master)(struct linked_list *results,int tasknb);
	void (*func_run_client)(struct linked_list *tasks,
		struct linked_list *results, int mrank, int tasknb);
};

void netbench_algo_run_master(enum netbench_algo_type algo,
	struct linked_list *results,int tasknb);
void netbench_algo_run_client(enum netbench_algo_type algo,
	struct linked_list *tasks,struct linked_list *results,int mrank,
	int tasknb);

#endif
