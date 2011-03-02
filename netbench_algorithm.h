#ifndef _NETBENCH_ALGORITHM_H
#define _NETBENCH_ALGORITHM_H

#include "netbench_algorithm_type.h"
#include "netbench_role.h"
#include "linked_list.h"

#include "netbench_algorithm_matrix.h"

#define NETBENCH_ALGO_INFO_LIST \
{ \
	{ NETBENCH_ALGO_MATRIX,netbench_algo_matrix_run }, \
	{ 0 } \
}

struct netbench_algo_info
{
	enum netbench_algo_type type;
	void (*func_run)(enum netbench_role role, struct linked_list *tasks,
		int mrank, int trank, int tasknb);
};

void netbench_algo_run(enum netbench_algo_type algo,enum netbench_role role,
	struct linked_list *tasks,int mrank,int trank,int tasknb);

#endif
