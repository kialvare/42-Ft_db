/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:47:28 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 14:51:41 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* Insert */

/* find_record(int fd, char *key): */
/* Reads from fd. If record with key is found the position of the beginning is returned. */
/* If record is not found, -1 is returned. */
off_t	find_record(int fd, char *key)
{
	printf("searching record...\n");
	off_t			pos;
	char			*line;
	char			**array;
	long long int	bytes_read;
	int				ret;

	pos = lseek(fd, 0, SEEK_SET);
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		bytes_read = ft_strlen(line);
		array = lsh_split_line(line, ",");
		if (ret == 0)
			return (-1);
		else if (!ft_strcmp(key, array[0]))
		{
			pos = lseek(fd, 0, SEEK_CUR);
			pos = lseek(fd, pos - bytes_read - 1, SEEK_SET);
			return (pos);
		}
		pos = lseek(fd, 0, SEEK_CUR);
	}
	return (-1);
}

/* Assumptions: iter_f (set to head_field of record) is  */
/* the Primary Key for that table */
int		insert_record(int fd, t_fields *record)
{
	int			ret;
	t_fields	*iter_f;

	iter_f = record;
	if (find_record(fd, iter_f->value) != -1)
	{
		printf("Record Already Exists\n");
		return (0);
	}
	ret = 0;
	printf("inserting...\n");
	while (iter_f)
	{
		ret += write(fd, iter_f->value, ft_strlen(iter_f->value));
		if (iter_f->next != NULL)
			ret += write(fd, ",", 1);
		iter_f = iter_f->next;
	}
	ret += write(fd, "\n", 1); 
	free(record);
	return (ret);
}

void	check_input(t_table table, char **input)
{
	t_col	*iter_c;
	int		i;

	i = 1;
	iter_c = table.header;
	iter_c = iter_c->next;
	while (iter_c)
	{
		if (!ft_strcmp(iter_c->type, "int") &&
				(ft_atoi(input[i]) == 0 && ft_strcmp(input[i], "0")))
		{
			printf("Incorrect input:(%s)\n",input[i]);
			printf("Incorrect input type for (%sn) Need:(%s)\n", iter_c->name, iter_c->type);
			exit(-1);
		}
		i++;
		iter_c = iter_c->next;
	}
}

int		handle_insert(int argc, char **argv)
{
	int			fd;
	t_table		*table;
	char		**array;
	t_fields	*record;
	t_fields	*iter_f;
	int			i;

	fd = 0;
	i = 1;
	record = NULL;
	if (argc ==  4 && !ft_strcmp(argv[1], "into"))
	{
		if((fd = open_record(argv[2])) == -1)
			return (0);
		table = build_table(fd);
		/* print_table(*table); */
		array = lsh_split_line(argv[3], ",()");
		check_input(*table, array);
		record = build_record(*table);
		iter_f = record;
		while (iter_f)
		{
			if (iter_f->is_prime)
				iter_f->value = ft_itoa(table->next_key);
			else
			{
				iter_f->value = array[i];
				i++;
			}
			iter_f = iter_f->next;
		}
		insert_record(fd, record);
		close_record(fd);
		return (1);
	}
	return (0);
}
