#include <stdlib.h>
#include <string.h>

#include "netbench_process.h"

struct netbench_process *
netbench_process_init(int num, char *name)
{
	struct netbench_process *ret;
	int size;

	ret = (struct netbench_process *) malloc(sizeof(struct netbench_process));
	ret->num = num;
	size = strlen(name) + 1;
	ret->name = (char *) malloc(size * sizeof(char));
	memcpy(ret->name,name,size);

	return ret;
}

void netbench_process_free(struct netbench_process *proc)
{
	free(proc->name);
	free(proc);
}
