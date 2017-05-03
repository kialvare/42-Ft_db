/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_record.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:50:24 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 14:54:57 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* Build Record Structure */
/* Creating Linked List structure of fields instead of a regular struct. */
/* Allows modular structure for different tables */

t_fields	*create_field(char *name)
{
	t_fields	*new;

	new = (t_fields *)malloc(sizeof(t_fields));
	new->header_name = name;
	new->value = NULL;
	new->is_prime = 0;
	new->is_foreign = 0;
	new->next = NULL;
	return (new);
}

t_fields	*add_field(t_fields *head, char *col_name)
{
	t_fields	*iter_f;

	iter_f = head;
	if (head == NULL)
	{
		head = create_field(col_name);
		head->is_prime = 1;
	}
	else
	{
		while (iter_f->next)
			iter_f = iter_f->next;
		iter_f->next = create_field(col_name);
	}
	return (head);
}

t_fields	*build_record(t_table table)
{
	t_fields	*record;
	t_col		*iter_col;

	record = NULL;
	iter_col = table.header;
	while (iter_col)
	{
		record = add_field(record, iter_col->name);
		iter_col = iter_col->next;
	}
	return (record);
}

void		free_fields(t_fields *head)
{
	t_fields	*cur;

	while ((cur = head))
	{
		free(cur);
		head = head->next;
	}
	free(head);
}
