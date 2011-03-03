#include "netbench_list_result.h"
#include "netbench_communication.h"
#include "linked_list.h"


void netbench_list_result_send(struct linked_list *results,int rank)
{
	unsigned int size;
	size = linked_list_size(results);

	if (!size)
		return;

	netbench_comm_list_send(size,rank);
	while (results)
	{
		netbench_result_send(results->value->u.res,rank);
		results = results->next;
	}
}

struct linked_list *
netbench_list_result_recv(struct linked_list *results, int rank)
{
	struct linked_list *ret;
	struct netbench_result *res;
	unsigned int size;

	if (results)
		ret = results;
	else
		ret = linked_list_init();

	size = netbench_comm_list_recv(rank);

	if (!size)
		return ret;

	while (size--)
	{
		res = netbench_result_recv(rank);
		linked_list_add(ret,linked_list_res_value_init(res));
	}

	return ret;
}

void netbench_list_result_print(struct linked_list *results)
{
	while (results)
	{
		if (results->value)
			netbench_result_print(results->value->u.res);
		results = results->next;
	}
}
