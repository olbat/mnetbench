#ifndef _NETBENCH_LIST_RESULT_H
#define _NETBENCH_LIST_RESULT_H

void netbench_list_result_send(struct linked_list *results,int drank);
struct linked_list *netbench_list_result_recv(int srank);

#endif
