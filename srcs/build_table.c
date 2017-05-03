/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:49:22 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 14:50:04 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"
/* Create Table Structure */

t_col	*new_header(char *name)
{
	t_col	*new;
	char	**split;

	split = lsh_split_line(name, "|");
	new = (t_col *)malloc(sizeof(t_col));
	new->data = NULL;
	new->type = split[1];
	new->name = split[0];
	new->count = 0;
	new->min = 0;
	new->max = 0;
	new->sum = 0;
	new->avg = 0;
	new->next = NULL;
	return (new);
}

t_col	*lstadd_header(t_col *head, char *name)
{
	if (!head)
		head = new_header(name);
	else if (head)
		head->next = lstadd_header(head->next, name);
	return (head);
}

t_tree	*new_data(int row, char *value)
{
	t_tree	*new;
	char	*cpy;

	cpy = ft_strnew(ft_strlen(value));
	ft_strcpy(cpy, value);
	new = (t_tree *)malloc(sizeof(t_tree));
	new->row = row;
	new->value = cpy;
	new->next = NULL;
	return (new);
}

t_tree	*lstadd_data(t_col *col, t_tree *head, int row, char *val)
{
	if (!head)
	{
		head = new_data(row, val);
		if (col->type && !ft_strcmp(col->type, "int"))
		{
			if (col->count == 0)
			{
				col->max = ft_atoi(val);
				col->min = ft_atoi(val);
				col->avg = ft_atoi(val);
				col->sum = ft_atoi(val);
			}
			else
			{
				if (col->max < ft_atoi(val))
					col->max = ft_atoi(val);
				if (col->min > ft_atoi(val))
					col->min = ft_atoi(val);
				col->sum += ft_atoi(val);
				col->avg = col->sum/col->count;
			}
		}
		col->count += 1;
	}
	else if (head)
		head->next = lstadd_data(col, head->next, row, val);
	return (head);
}

t_table	*build_table(int fd)
{
	t_table	*table;
	char	*line;
	char	**array;
	int		ret;
	int		row;
	t_col	*iter_h;

	ret = 0;
	table = (t_table*)malloc(sizeof(t_table));

	/* setting meta data */
	table->header = NULL;
	get_next_line(fd, &line);
	array = lsh_split_line(line, ",");
	array++;
	while (*array)
	{
		table->header = lstadd_header(table->header, *array);
		array++;
	}
	get_next_line(fd, &line);
	array = lsh_split_line(line, ",");
	table->col_count = ft_atoi(array[1]);
	row = 3;
	/* Setting Column data */
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (ret == 0)
		{
			lseek(fd, 0, SEEK_SET);
			return (table);
		}
		iter_h = table->header;
		array = lsh_split_line(line, ",");
		if (ft_atoi(*array))
		{
			table->next_key = ft_atoi(*array) + 1;
			while (*array)
			{
				iter_h->data = lstadd_data(iter_h, iter_h->data, row, *array);
				array++;
				iter_h = iter_h->next;
			}
		}
		row++;
	}
	lseek(fd, 0, SEEK_SET);
	return (table);
}

void	print_table(t_table table)
{
	printf("=============Printing Table=========\n");
	t_col	*iter_col;
	t_tree	*iter_tree;

	iter_col = table.header;
	while (iter_col)
	{
		printf("%s->", iter_col->name);
		iter_tree = iter_col->data;
		while (iter_tree)
		{
			printf("(row#:%d, val:%s),", iter_tree->row, (char *)iter_tree->value);
			iter_tree = iter_tree->next;
		}
		printf("\n");
		printf("col->count:%d\n", iter_col->count);
		printf("col->min:%d\n", iter_col->min);
		printf("col->max:%d\n", iter_col->max);
		printf("col->sum:%d\n", iter_col->sum);
		printf("col->avg:%d\n", iter_col->avg);
		iter_col = iter_col->next;
	}
	printf("=====End Table =======\n");
} 
