#include "netbench_algorithm_matrix.h"

#include "linked_list.h"
#include "netbench_task.h"
#include "netbench_list_task.h"
#include "netbench_role.h"
#include "mnetbench.h"

void netbench_algo_matrix_run(
	enum netbench_role role,
	struct linked_list *tasks,
	int mrank,
	int trank,
	int tasknb
)
{
	if (role == NETBENCH_ROLE_TESTER)
	{
		int i;
		i = tasknb;
		while (i--)
		{
			if ((i != mrank) && (i != NETBENCH_MASTER_RANK))
				netbench_list_task_run(tasks,role,mrank,i);
		}
	}
	else
		netbench_list_task_run(tasks,role,mrank,trank);
}
