#ifndef _NETBENCH_PRINTER_H
#define _NETBENCH_PRINTER_H

#include "netbench_printer_type.h"
#include "linked_list.h"
#include "options.h"

#define NETBENCH_PRINTER_INFO_LIST \
{ \
	{ NETBENCH_PRINTER_CLASSIC, OPT_FLAG_PRINTER_CLASSIC, \
		netbench_printer_print_classic }, \
	{ NETBENCH_PRINTER_HTML, OPT_FLAG_PRINTER_HTML, \
		netbench_printer_print_html }, \
	{ NETBENCH_PRINTER_MATRIX, 0, 0 }, \
	{ NETBENCH_PRINTER_NONE, 0, 0 } \
}
	

struct netbench_printer_info
{
	enum netbench_printer_type type;
	enum option_flag optflag;
	void (*func)(enum netbench_printer_type prtype,
		enum netbench_test_type tetype,struct linked_list *results,
		unsigned int clientsnb);
};

void netbench_printer_print(struct linked_list *results,unsigned int clientsnb,
	options_t opt);
void netbench_printer_print_single(enum netbench_printer_type prtype,
	enum netbench_test_type tetype,struct linked_list *results,
	int srank,int drank);
void netbench_printer_print_classic(enum netbench_printer_type prtype,
	enum netbench_test_type tetype,struct linked_list *results,
	unsigned int clientsnb);
void netbench_printer_print_html(enum netbench_printer_type prtype,
	enum netbench_test_type tetype,struct linked_list *results,
	unsigned int clientsnb);

#endif
