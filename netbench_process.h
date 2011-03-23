#ifndef _NETBENCH_PROCESS_H
#define _NETBENCH_PROCESS_H

struct netbench_process
{
	int num;
	char *name;
};

struct netbench_process *netbench_process_init(int num, char *name);
void netbench_process_free(struct netbench_process *proc);

#endif
