/*
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

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H


enum linked_list_type
{
	LKD_TYPE_RESULT,
	LKD_TYPE_TASK
};

struct linked_list_value
{
	enum linked_list_type type;
	union linked_list_union
	{
		struct netbench_result *res;
		struct netbench_task *task;
	} u;
};

struct linked_list
{
	struct linked_list_value *value;
	struct linked_list *next;
};


struct linked_list *linked_list_init();
void linked_list_free(struct linked_list *);
struct linked_list_value *linked_list_add(struct linked_list *,struct linked_list_value *);
void linked_list_value_free(struct linked_list_value *);


#include "netbench_result.h"
struct linked_list_value *linked_list_res_value_init(struct netbench_result *res);
void linked_list_res_value_free(struct linked_list_value *val);

#include "netbench_task.h"
struct linked_list_value *linked_list_task_value_init(struct netbench_task *task);
void linked_list_task_value_free(struct linked_list_value *val);

#endif
