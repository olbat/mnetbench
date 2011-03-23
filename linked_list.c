/* This file is a part of groinc
 * 
 * Copyright (C) 2006, 2007 Sarzyniec Luc <olbat@xiato.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * see the COPYING file for more informations */

#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

#include "netbench_result.h"
#include "netbench_task.h"
#include "netbench_process.h"


struct linked_list *linked_list_init()
{
	struct linked_list *ret;
	ret = (struct linked_list *) malloc(sizeof(struct linked_list));
	ret->next = 0;
	ret->value = 0;
	return ret;
}

void linked_list_free(struct linked_list *l)
{
	struct linked_list *ptr;
	ptr = l;
	while (l)
	{
		ptr = l;
		l = l->next;
		linked_list_value_free(ptr->value);
		free(ptr);
	}
}

struct linked_list_value *
linked_list_add(
	struct linked_list *l,
	struct linked_list_value *val
)
{
	if (l->value)
	{
		struct linked_list *ptr;
		ptr = l;
		while (l->next)
			l = l->next;
		l->next = linked_list_init(); 
		l = l->next;
	}
	l->value = val;
	return val;
}

__inline__ unsigned int 
linked_list_size(struct linked_list *list)
{
	unsigned int ret;
	ret = 0;

	while (list)
	{
		if (list->value)
			ret++;
		list = list->next;
	}

	return ret;
}

struct linked_list_value *
linked_list_res_value_init(struct netbench_result *res)
{
	struct linked_list_value *ret;

	ret = (struct linked_list_value *)
		malloc(sizeof(struct linked_list_value));
	ret->type = LKD_TYPE_RESULT;

	ret->u.res = res;

	return ret;
}

void linked_list_res_value_free(struct linked_list_value *val)
{
	netbench_result_free(val->u.res);
	free(val);
}

struct linked_list_value *
linked_list_task_value_init(struct netbench_task *task)
{
	struct linked_list_value *ret;

	ret = (struct linked_list_value *)
		malloc(sizeof(struct linked_list_value));
	ret->type = LKD_TYPE_TASK;

	ret->u.task = task;

	return ret;
}

void linked_list_task_value_free(struct linked_list_value *val)
{
	netbench_task_free(val->u.task);
	free(val);
}

struct linked_list_value *
linked_list_proc_value_init(struct netbench_process *proc)
{
	struct linked_list_value *ret;

	ret = (struct linked_list_value *)
		malloc(sizeof(struct linked_list_value));
	ret->type = LKD_TYPE_PROC;

	ret->u.proc = proc;

	return ret;
}

void linked_list_proc_value_free(struct linked_list_value *val)
{
	netbench_process_free(val->u.proc);
	free(val);
}

void linked_list_value_free(struct linked_list_value *val)
{
	if (val)
	{
		switch (val->type)
		{
			case LKD_TYPE_RESULT : 
				linked_list_res_value_free(val);
				break;
			case LKD_TYPE_TASK :
				linked_list_task_value_free(val);
				break;
			case LKD_TYPE_PROC :
				linked_list_proc_value_free(val);
				break;
		}
	}
}
