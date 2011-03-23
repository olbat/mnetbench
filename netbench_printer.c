#include <stdio.h>

#include "netbench_printer.h"
#include "netbench_printer_type.h"
#include "linked_list.h"
#include "netbench_result.h"
#include "mnetbench.h"
#include "options.h"
#include "netbench_test.h"

__inline__ void netbench_printer_print(
	struct linked_list *processes,
	struct linked_list *results,
	unsigned int clientsnb,
	options_t opts
)
{
	static struct netbench_test_info testinfolist[] =
		NETBENCH_TEST_INFO_LIST;
	static struct netbench_printer_info printerinfolist[] =
		NETBENCH_PRINTER_INFO_LIST;
	struct netbench_test_info *testptr;
	struct netbench_printer_info *prptr;

	testptr = testinfolist;

	while (testptr->type != NETBENCH_TEST_NONE)
	{
		if (OPT_GET(opts,testptr->optflag))
		{
			prptr = printerinfolist;
			while (prptr->type != NETBENCH_PRINTER_NONE)
			{
				if (OPT_GET(opts,prptr->optflag))
				{
					prptr->func(prptr->type,testptr->type,
						processes,results,clientsnb);
				}
				prptr++;
			}
		}
		testptr++;
	}
}

__inline__ void netbench_printer_print_single(
	enum netbench_printer_type prtype,
	enum netbench_test_type tetype,
	struct linked_list *results,
	int srank,
	int drank
)
{
	__typeof__(results) ptr;
	struct netbench_result *resptr;

	ptr = results;
	resptr = ptr->value->u.res;
	while ((ptr)
		&& (
			(resptr->srank != srank) 
			|| (resptr->drank != drank)
			|| (resptr->type != tetype)
		)
	)
	{
		if (ptr->value)
			resptr = ptr->value->u.res;
		else
			resptr = 0;
		ptr = ptr->next;
	}

	if ((resptr) && (resptr->srank == srank) && (resptr->drank == drank)
		&& (resptr->type == tetype)
	)
		netbench_result_print(prtype,resptr);
	else
		fprintf(stdout,"N/A");
}

void netbench_printer_print_classic(
	enum netbench_printer_type prtype,
	enum netbench_test_type tetype,
	struct linked_list *processes,
	struct linked_list *results,
	unsigned int clientsnb
)
{
	while (processes)
	{
		if (processes->value)
		{
			fprintf(stdout,"Process %d is %s\n",
				processes->value->u.proc->num,
				processes->value->u.proc->name
			);
		}
		processes = processes->next;
	}
	while (results)
	{
		if ((results->value) && (results->value->u.res->type == tetype))
			netbench_result_print(prtype,results->value->u.res);
		results = results->next;
	}
}

void netbench_printer_print_html(
	enum netbench_printer_type prtype,
	enum netbench_test_type tetype,
	struct linked_list *processes,
	struct linked_list *results,
	unsigned int clientsnb
)
{
	unsigned int i,j;

	fprintf(stdout,"<h1>%s tests results</h1>",
		netbench_test_type_name(tetype));
	fprintf(stdout,"<table border=1>\n<tr><th>#</th>");

	i = 0;
	while (i < clientsnb) 
	{
		if (i == NETBENCH_MASTER_RANK)
		{
			i++;
			continue;
		}

		fprintf(stdout,"<th>%d</th>",i);
		i++;
	}
	fprintf(stdout,"</tr>\n");
		

	i = 0;
	while (i < clientsnb)
	{
		if (i == NETBENCH_MASTER_RANK)
		{
			i++;
			continue;
		}

		fprintf(stdout,"<tr><td>%d</td>",i);
		j = 0;
		while (j < clientsnb)
		{
			if (j == NETBENCH_MASTER_RANK)
			{
				j++;
				continue;
			}

			fprintf(stdout,"<td align=\"center\">");
			netbench_printer_print_single(prtype,tetype,results,i,j);
			fprintf(stdout,"</td>");
			j++;
		}
		fprintf(stdout,"</tr>\n");
		i++;
	}
	fprintf(stdout,"</table>\n");
	fprintf(stdout,"<h1>Processes</h1>\n");
	fprintf(stdout,"<table border=1><tr><th>#</th><th>Hostname</th></tr>\n");
	while (processes)
	{
		if (processes->value)
		{
			fprintf(stdout,"<tr><td>%d</td><td>%s</td></tr>\n",
				processes->value->u.proc->num,
				processes->value->u.proc->name
			);
		}
		processes = processes->next;
	}
	fprintf(stdout,"</table>\n");
}
