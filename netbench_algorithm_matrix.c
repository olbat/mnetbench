#include "netbench_algorithm_matrix.h"

#include "linked_list.h"
#include "netbench_task.h"
#include "netbench_list_task.h"
#include "netbench_list_result.h"
#include "netbench_role.h"
#include "mnetbench.h"
#include "netbench_communication.h"

void netbench_algo_matrix_run_client(
	struct linked_list *tasks,
	struct linked_list *results,
	int mrank,
	int tasknb
)
{
	enum netbench_role role;
	int tot;
	tot = tasknb - 1;

	while (tot--)
	{
		role = netbench_comm_role_recv(NETBENCH_MASTER_RANK);
		if (role == NETBENCH_ROLE_TESTER)
		{
			int i;

			i = tasknb;
			while (i--)
			{
				if ((i != mrank) && (i != NETBENCH_MASTER_RANK))
					netbench_list_task_run(tasks,role,mrank,i);
			}
			netbench_list_result_send(results,NETBENCH_MASTER_RANK);
		}
		else
		{
			int trank;
			trank = netbench_comm_rank_recv(NETBENCH_MASTER_RANK);
			netbench_list_task_run(tasks,role,mrank,trank);
		}
	}
}

void netbench_algo_matrix_run_master(struct linked_list *results, int tasknb)
{
	int i, j;

	i = tasknb;

	while (i--)
	{
		if (i == NETBENCH_MASTER_RANK)
			continue;
		j = tasknb;

		while (j--)
		{
			if (j == NETBENCH_MASTER_RANK)
				continue;
			/* tester node */
			if (j == i)
			{
				netbench_comm_role_send(NETBENCH_ROLE_TESTER,j);
			}
			/* tested nodes */
			else
			{
				netbench_comm_role_send(NETBENCH_ROLE_TESTED,j);
				netbench_comm_rank_send(i,j);
			}
		}
		netbench_list_result_recv(results,i);
	}
}
