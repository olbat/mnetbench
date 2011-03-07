#ifndef _NETBENCH_PRINTER_H
#define _NETBENCH_PRINTER_H

#include "netbench_printer_type.h"
#include "linked_list.h"

void netbench_printer_print(enum netbench_printer_type prtype,
	enum netbench_test_type tetype,struct linked_list *results,
	unsigned int clientsnb);
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
