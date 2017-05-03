/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:46:14 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 15:06:40 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* SELECT SQL Command*/

/* scan argument after "command key word". Treats arg as filename */
char	*scan_for_file(char *command, char **argv)  
{
	int			i;

	i = 0;
	while (*argv[i])
	{
		if (!ft_strcmp(argv[i++], command))
		{
			if (argv[i])
				return (argv[i]);
		}
	}
	return (NULL);
}

/* Beta */
/* char	**scan_for_file_multi(char *command, char **argv) */
/* { */
/* 	int			i; */
/* 	int			j; */
/* 	char		**file_list; */
/*  */
/* 	i = 0; */
/* 	j = 0; */
/* 	file_list = (char **)malloc(sizeof(char *) * 4); */
/* 	while (argv[i] && ft_strcmp(argv[i], command)) */
/* 	{ */
/* 		printf("argv:%s\n", argv[i]); */
/* 		i++; */
/* 	} */
/* 	i++; */
/* 	while (argv[i] && ft_strcmp(argv[i], "where")) */
/* 	{ */
/* 		printf("argv:%s\n", argv[i]); */
/* 		file_list[j] = argv[i]; */
/* 		i++; */
/* 		j++; */
/* 	} */
/* 	return (file_list); */
/* } */

/* returns string of arguments between "select" and "from" */
char	**parse_col_list(char **argv) 
{
	int		i;
	int		j;
	char	**col_list;

	i = 1;
	col_list = NULL;
	while (ft_strcmp(argv[i++], "from"))
	{
	}
	col_list = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	i = 1;
	while (ft_strcmp(argv[i], "from"))
	{
		col_list[j++] = argv[i];
		i++;
	}
	col_list[j] = 0;
	return (col_list);
}

/* converts return (see parse_col_list) to int index list */
int		convert_to_index(int **colist_index, char **col_list, t_table *table) 
{
	t_col	*temp_col;
	int		i;
	int		j;
	int		index;
	int		col_count;
	
	temp_col = table->header;
	i = 0;
	j = 0;
	while (col_list[i])
		i++;
	*colist_index = (int *)malloc(sizeof(int) * i);
	col_count = i;
	i = 0;
	while (col_list[i])
	{
		index = 0;
		temp_col = table->header;
		while (temp_col)
		{
			if (!strcmp(col_list[i], temp_col->name))
			{
				(*colist_index)[j] = index;
				j++;
				break;
			}
			index++;
			temp_col = temp_col->next;
		}
		i++;
	}
	return (col_count);
}

int		is_selected_column(int index, int *indexlist, int col_count)
{
	int i;
	int len;

	i = 0;
	len = col_count;
	while (i < len)
	{
		if (index == indexlist[i])
			return (1);
		i++;
	}
	return (0);
}

int		valid_column(char **col_list, t_table table)
{
	int		i;
	t_col	*iter_c;
	int		match;

	i = 0;
	while (col_list[i])
	{
		match = 0;
		iter_c = table.header;
		while (iter_c)
		{
			if (!ft_strcmp(col_list[i], iter_c->name))
			{
				match = 1;
				break;
			}
			iter_c = iter_c->next;
		}
		if (match == 0)
			return (0);
		i++;
	}
	return (1);
}

void	print_record(int fd, int *row_list, char **col_list, t_table table)
{
	char 	*line;
	int		curr_row;
	int		i;
	char	**array;
	int		*colist_index;
	int		usr_col_count;
	
	colist_index = NULL;
	curr_row = 0;
	i = 0;
	while (*row_list)
	{
		lseek(fd, 0, SEEK_SET);
		curr_row = 0;
		while (curr_row != *row_list && (get_next_line(fd, &line)) != -1)
			curr_row++;
		array = lsh_split_line(line, ",");
		if (!col_list)
		{
			while (*array)
			{
				printf("%s|", *array);
				array++;
			}
			printf("\n");
		}
		else if (valid_column(col_list, table))
		{
			i = 0;
			usr_col_count = convert_to_index(&colist_index, col_list, &table);
			while (array[i])
			{
				if (is_selected_column(i, colist_index, usr_col_count))
					printf("%s|", array[i]);
				i++;
			}
			printf("\n");
		}
		else
			exit(1);
		free(line);
		row_list++;
	}
}

/* Handling Aggregate Functions */

char	**is_aggregate(char **col_list)
{
	char	**array;
	
	array = NULL;
	array = lsh_split_line(col_list[0], "()");
	if (!ft_strcmp(array[0], "count")
		|| !ft_strcmp(array[0], "min")
		|| !ft_strcmp(array[0], "max")
		|| !ft_strcmp(array[0], "sum")
		|| !ft_strcmp(array[0], "avg"))
		return (array);
	return (NULL);
}

void	print_aggregate(t_table *table, char **aggr_list)
{
	t_col	*iter_c;
	
	iter_c = table->header;
	while (iter_c && ft_strcmp(iter_c->name, aggr_list[1]))
		iter_c = iter_c->next;
	if (!ft_strcmp(aggr_list[0], "count"))
		printf("%d\n", iter_c->count);
	else if (!ft_strcmp(aggr_list[0],"min"))
		printf("%d\n", iter_c->min);
	else if (!ft_strcmp(aggr_list[0],"max"))
		printf("%d\n", iter_c->max);
	else if (!ft_strcmp(aggr_list[0],"sum"))
		printf("%d\n", iter_c->sum);
	else if (!ft_strcmp(aggr_list[0],"avg"))
		printf("%d\n", iter_c->avg);
}

/* Return list of Row Numbers of data that satisfy "Constraint */
int		*select_record(char **col, t_table *table, char *Constraint) 
{
	int		*rows;
	t_tree	*temp;
	t_col	*temp_col;
	int		i;
	char	**array;
	/* char	op; */

	/* valid_col(col, table); */
	i = 0;
	rows = (int *)malloc(sizeof(int) * table->header->count + 1);
	if (Constraint)
	{
		temp_col = table->header;
		/* if(ft_strchr(Constraint, '=')) */ 						// Not yet implemented: for comparing constraints
		/* 	op = '='; */
		/* if(ft_strchr(Constraint, '>')) */
		/* 	op = '>'; */
		/* if(ft_strchr(Constraint, '<')) */
		/* 	op = '<'; */
		array = lsh_split_line(Constraint, "=><");
		while (ft_strcmp(temp_col->name, array[0]))
			temp_col = temp_col->next;
		temp = temp_col->data;
		while (temp)
		{
			if (!ft_strcmp((*temp).value, array[1]))
			{
				rows[i] = (*temp).row;
				i++;
			}
			temp = temp->next;
		}
		rows[i] = 0;
	}
	else
	{
		temp = table->header->data;
		while (temp)
		{
			rows[i] = (*temp).row;
			temp = temp->next;
			i++;
		}
		rows[i] = 0;
	}
	(void)col;
	return (rows);
}

int		handle_select(int argc, char **argv)
{
	int			fd;
	t_table		*table;
	char		*file;
	/* char		**file_list; */
	char		**col_list;
	char		*constraint;
	int			*row_list;
	char		**aggr_list;

	/* file_list = scan_for_file_multi("from", argv); */
	table = NULL;
	file = scan_for_file("from", argv);
	col_list = NULL;
	constraint = get_constraint(argv);
	if (argc > 3 && file)
	{
		if((fd = open_record(file)) == -1)
			return (0);
		col_list = parse_col_list(argv);
		/* if (!constraint) */
			table = build_table(fd);
		/* else */
		/* 	table = build_table_constraint(fd); */
		/* print_table(*table); */
		row_list = select_record(col_list, table, constraint); // return list of rows in the data file that satisfy constraint
		/* validate_column_list(table, col_list); */
		if (col_list)
		{
			if (!ft_strcmp(col_list[0], "*"))
				print_record(fd, row_list, NULL, *table);
			else if ((aggr_list = is_aggregate(col_list)))
				print_aggregate(table, aggr_list);
			else
				print_record(fd, row_list, col_list, *table);
		}
		close_record(fd);
	}
	return (1);
}
