#ifndef _NETBENCH_LIST_RESULT_H
#define _NETBENCH_LIST_RESULT_H

#include "linked_list.h"

void netbench_list_result_send(struct linked_list *results,int rank);
struct linked_list *netbench_list_result_recv(struct linked_list *res,int rank);

#endif
