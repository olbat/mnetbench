#include "netbench_algorithm.h"

__inline__ struct netbench_algo_info *
netbench_algo_info_fetch(enum netbench_algo_type type)
{
	struct netbench_algo_info *ptr;
	struct netbench_algo_info algoinfolist[] = NETBENCH_ALGO_INFO_LIST;

	ptr = algoinfolist;

	while ((ptr) && (ptr->type != type))
		ptr++;
	
	return ptr;
}

void netbench_algo_run_master(
	enum netbench_algo_type algo,
	struct linked_list *results,
	int tasknb
)
{
	struct netbench_algo_info *info;
	info = netbench_algo_info_fetch(algo);

	info->func_run_master(results,tasknb);
}

void netbench_algo_run_client(
	enum netbench_algo_type algo,
	struct linked_list *tasks,
	struct linked_list *results,
	int mrank,
	int tasknb
)
{
	struct netbench_algo_info *info;
	info = netbench_algo_info_fetch(algo);

	info->func_run_client(tasks,results,mrank,tasknb);
}
