/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:44:01 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 17:22:54 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* UPDATE SQL Command*/

char	*get_constraint(char **argv)
{
	int i;
	char	*constraint;
	
	i = 0;
	constraint = NULL;
	while (argv[i] && ft_strcmp(argv[i], "where"))
		i++;
	if (!argv[i])
		return (constraint);
	i++;
	if (argv[i])
		constraint = argv[i];
	return (constraint);
}

char	*get_set(char **argv)
{
	int i;
	char	*constraint;
	
	i = 0;
	constraint = NULL;
	while (argv[i] && ft_strcmp(argv[i], "set"))
		i++;
	i++;
	if (argv[i])
		constraint = argv[i];
	return (constraint);
}

void	update_fields(t_fields *rec, char **con_array, char **array, t_table table)
{
	t_fields	*iter_f;
	t_col		*iter_c;
	int			i;

	iter_c = table.header;
	while (iter_c && ft_strcmp(iter_c->name, con_array[0]))
		iter_c = iter_c->next;
	iter_f = rec;
	i = 0;
	while (iter_f)
	{
		if (!strcmp(con_array[0], iter_f->header_name))
			iter_f->value = con_array[1];
		else
			iter_f->value = array[i];
		if (!ft_strcmp(iter_c->type, "int") && (!atoi(iter_f->value) && ft_strcmp(iter_f->value, "0")))
		{
			printf("Invalid type for (%s). Need (%s)\n", iter_c->name, iter_c->type);
			exit(-2);
		}
		i++;
		iter_f = iter_f->next;
	}
	(void)table;
}

void	set_print_record(int fd, int fd_a, int *row_list, char **col_list, t_table table, char *constraint)
{
	char 	*line;
	int		curr_row;
	int		i;
	char	**array;
	char 	**con_array;
	int		*colist_index;
	t_fields	*rec_t;

	rec_t = NULL;
	(void)col_list;
	colist_index = NULL;
	curr_row = 0;
	i = 0;
	con_array = lsh_split_line(constraint, "=");
	while (*row_list)
	{
		lseek(fd, 0, SEEK_SET);
		curr_row = 0;
		while (curr_row != *row_list && (get_next_line(fd, &line)) != -1)
			curr_row++;
		array = lsh_split_line(line, ",");
		rec_t = build_record(table);
		update_fields(rec_t, con_array, array, table);
		delete_record(fd, array[0]);
		insert_record(fd_a, rec_t);
		free(line);
		row_list++;
	}
}

/* update roster.db set fname=potato where fname=kim */
int		handle_set(int argc, char **argv)
{
	int			fd;
	int 		fd_a;
	t_table		*table;
	char		*file;
	char		**col_list;
	char		*constraint;
	char 		*set_constraint;
	int			*row_list;

	file = scan_for_file("update", argv);
	col_list = (char **)malloc(sizeof(char *) * 2);
	col_list[0] = "*";
	col_list[1] = NULL;
	constraint = get_constraint(argv);
	set_constraint = argv[3];
	if (argc >= 6 && file)
	{
		if((fd = open_record_delete(file)) == -1)
			return (0);
		if((fd_a = open_record(file)) == -1)
			return (0);
		table = build_table(fd);
		row_list = select_record(col_list, table, constraint);
		set_print_record(fd, fd_a, row_list, NULL, *table, set_constraint);
		close_record(fd);
	}
	return (1);
}
