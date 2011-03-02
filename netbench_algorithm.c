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

void netbench_algo_run(
	enum netbench_algo_type algo,
	enum netbench_role role,
	struct linked_list *tasks,
	int mrank,
	int trank,
	int tasknb
)
{
	struct netbench_algo_info *info;
	info = netbench_algo_info_fetch(algo);

	info->func_run(role,tasks,mrank,trank,tasknb);
}
