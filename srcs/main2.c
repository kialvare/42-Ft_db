/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:31:05 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 11:45:03 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"
/******************************************************/
/**              funtion prototypes                  **/
/******************************************************/
int argc_len(char **argv);
int open_record(char *filename);
int open_record_delete(char *filename);
void close_record(int fd);
off_t find_record(int fd, char *key);
int *select_record(char **col, t_table *table, char *Constraint);
int delete_record(int fd, char *key);
t_col *new_header(char *name);
t_col *lstadd_header(t_col *head, char *name);
t_tree *new_data(int row, char *value);
t_tree *lstadd_data(t_col *col, t_tree *head, int row, char *val);
t_table *build_table(int fd);
t_table *build_table_constraint(int fd, int *row_list);
void print_table(t_table table);
t_fields *create_field(char *name);
t_fields *add_field(t_fields *head, char *col_name);
t_fields *build_record(t_table table);
void free_fields(t_fields *head);
int insert_record(int fd, t_fields *record);
int handle_insert(int argc, char **argv);
int handle_delete(int argc, char **argv);
char *scan_for_file(char *command, char **argv);
char **parse_col_list(char **argv);
int convert_to_index(int **colist_index, char **col_list, t_table *table);
int is_selected_column(int index, int *indexlist, int col_count);
int valid_column(char **col_list, t_table table);
void print_record(int fd, int *row_list, char **col_list, t_table table);
char **is_aggregate(char **col_list);
void print_aggregate(t_table *table, char **aggr_list);
int handle_select(int argc, char **argv);
char *get_constraint(char **argv);
char *get_set(char **argv);
void update_fields(t_fields *rec, char **con_array, char **array, t_table table);
void set_print_record(int fd, int fd_a, int *row_list, char **col_list, t_table table, char *constraint);
int handle_set(int argc, char **argv);
int sql(char *op, char **argv, char *line);
char **lsh_split_line(char *line, const char *delim);
int sql_execute(char **args, char *line);
char *lsh_read_line(void);
char **scan_for_file_multi(char *command, char **argv);
unsigned int assign_key(t_table table);
char **parse_values(char **values);

/* lseek(fd, 0, SEEK_SET);   #<{(| seek to start of file |)}># */
/* lseek(fd, 100, SEEK_SET); #<{(| seek to offset 100 from the start |)}># */
/* lseek(fd, 0, SEEK_END);   #<{(| seek to end of file (i.e. immediately after the last byte) |)}># */
/* lseek(fd, -1, SEEK_END);  #<{(| seek to the last byte of the file |)}># */
/* lseek(fd, -10, SEEK_CUR); #<{(| seek 10 bytes back from your current position in the file |)}># */
/* lseek(fd, 10, SEEK_CUR);  #<{(| seek 10 bytes ahead of your current position in the file |)}># */
/*  */

/* Helper Functions */
int		argc_len(char **argv)
{
	char	**temp;
	int		count;

	temp = argv;
	count = 0;
	while (*temp)
	{
		count++;
		temp++;
	}
	return (count);
}

/* file-reading */
int		open_record(char *filename)
{
	int fd;

	fd = open(filename, O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		perror("open_record");
	return fd;
}

int		open_record_delete(char *filename)
{
	int fd;

	fd = open(filename, O_RDWR , 0644);
	if (fd == -1)
	{
		perror("Table Does not Exist");
		exit(-1);
	}
	return fd;
}

void	close_record(int fd)
{
	close(fd);
}

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

/* Beta */
/* t_table	*build_table_constraint(int fd, int *row_list) */
/* { */
/* 	t_table	*table; */
/* 	char	*line; */
/* 	char	**array; */
/* 	int		ret; */
/* 	int		row; */
/* 	t_col	*iter_h; */
/* 	int		i; */
/*  */
/* 	ret = 0; */
/* 	table = (t_table*)malloc(sizeof(t_table)); */
/*  */
/* 	#<{(| setting meta data |)}># */
/* 	table->header = NULL; */
/* 	get_next_line(fd, &line); */
/* 	array = lsh_split_line(line, ","); */
/* 	array++; */
/* 	while (*array) */
/* 	{ */
/* 		table->header = lstadd_header(table->header, *array); */
/* 		array++; */
/* 	} */
/* 	get_next_line(fd, &line); */
/* 	array = lsh_split_line(line, ","); */
/* 	table->col_count = ft_atoi(array[1]); */
/* 	row = 3; */
/* 	i = 0; */
/* 	#<{(| Setting Column data |)}># */
/* 	while (row_list[i] && (ret = get_next_line(fd, &line)) != -1) */
/* 	{ */
/* 		if (ret == 0) */
/* 		{ */
/* 			lseek(fd, 0, SEEK_SET); */
/* 			return (table); */
/* 		} */
/* 		if (row == row_list[i]) */
/* 		{ */
/* 			iter_h = table->header; */
/* 			array = lsh_split_line(line, ","); */
/* 			if (**array != '*') */
/* 			#<{(| if (ft_atoi(*array)) |)}># */
/* 			{ */
/* 				table->next_key = ft_atoi(*array) + 1; */
/* 				while (*array) */
/* 				{ */
/* 					iter_h->data = lstadd_data(iter_h, iter_h->data, row, *array); */
/* 					array++; */
/* 					iter_h = iter_h->next; */
/* 				} */
/* 			} */
/* 			i++; */
/* 		} */
/* 		row++; */
/* 	} */
/* 	lseek(fd, 0, SEEK_SET); */
/* 	return (table); */
/* } */

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

/* Handle SQL Commands */

/* Insert */

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

/* DELETE SQL Command*/

int		delete_record(int fd, char *key)
{
	printf("deleting...\n");
	int		ret;
	char	*line;
	char	**array;
	int		delete_bytes;
	off_t	pos;
	
	pos = lseek(fd, 0, SEEK_SET);								//resets the fd position
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		delete_bytes = ft_strlen(line);
		array = lsh_split_line(line, ",");
		if (ret == 0)
			return (ret);
		else if (!ft_strcmp(key, array[0]))
		{
			pos = lseek(fd, 0, SEEK_CUR);
			pos = lseek(fd, pos - delete_bytes - 1, SEEK_SET);
			printf("deleting [%d] bytes\n", delete_bytes);
			ft_bzero(line, delete_bytes);
			ret = write(fd, &line, delete_bytes);
			return (ret);
		}
		pos = lseek(fd, 0, SEEK_CUR);
	}
	return (ret);
}

int		handle_delete(int argc, char **argv)
{
	int	fd;
	/* t_table	*table; */

	if (argc > 3 && !ft_strcmp(argv[1], "from"))
	{
		if((fd = open_record_delete(argv[2])) == -1)
			return (0);
		/* table = build_table(fd); */
		delete_record(fd, argv[3]);
		close_record(fd);
		return (1);
	}
	return (0);
}

/* SELECT SQL Command*/

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

/* Should Return a list of Row # that satisfy Constraints
 * If Constrain is NULL all row numbers with data is returned */
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
		table = build_table(fd);
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

/* UPDATE SQL Command*/

char	*get_constraint(char **argv)
{
	int i;
	char	*constraint;
	
	i = 0;
	constraint = NULL;
	while (argv[i] && ft_strcmp(argv[i], "where"))
		i++;
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
	int			i;

	iter_f = rec;
	i = 0;
	while (iter_f)
	{
		if (!strcmp(con_array[0], iter_f->header_name))
			iter_f->value = con_array[1];
		else
			iter_f->value = array[i];
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

/* MiniShell Section */
int 	sql(char *op, char **argv, char *line)
{
	int	argc;
	/* person_rec	rec; */

	argc = 0;
	argc = argc_len(argv);
	/* print_table(*table); */
	if (argc >= 1)
	{
		/* insert */
		if (!strcmp(op, "insert"))
		{
			/* if(!handle_insert(argc, argv, &rec)) */
			if(!handle_insert(argc, argv))
			{
				printf("Error: Incomplete SQL:%s\n", line);
				return (1);
			}
		}
		/* delete */
		if (!strcmp(op, "delete"))
		{
			if(!handle_delete(argc, argv))
			{
				printf("Error: Incomplete SQL:%s\n", line);
				return (1);
			}
		}
		/* select */
		if (!strcmp(op, "select"))
		{
			if (!handle_select(argc, argv))
			{
				printf("Error: Incomplete SQL:%s\n", line);
				return (1);
			}
		}
		/* set */
		if (!strcmp(op, "update"))
		{
			if(!handle_set(argc, argv))
			{
				printf("Error: Incomplete SQL:%s\n", line);
				return (1);
			}
		}
	}
	return (1);
}

char	**lsh_split_line(char *line, const char *delim)
{
	int	bufsize = LSH_TOK_BUFSIZE;
	int	position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delim);
	while (token != NULL) {
		tokens[position] = token; position++;

		if (position >= bufsize) {
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[position] = NULL;
	return tokens;
}

int		sql_execute(char **args, char *line)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid < 0)
  {
	  // Error forking
  	perror("sql");
  }
  else if (pid == 0)
  {
    // Child process
    if (sql(args[0], args, line) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  }
  else
  {
    // Parent process
    do
	{
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

char	*lsh_read_line(void)
{
  char *line = NULL;
  /* size_t bufsize = 0; // have getline allocate a buffer for us */

  get_next_line(0, &line);
  /* getline(&line, &bufsize, stdin); */
  return line;
}

int main(void)
{
	char	*line;
	char	*user_input;
	char	**args;
	int		status;

	status = 1;
	line = NULL;
	do{
		ft_printf("SqLit\u27a6 ");
		line = lsh_read_line();
		user_input = strdup(line);
		args = lsh_split_line(line, " ");
		status = sql_execute(args, user_input);
		free(line);
		free(args);
	} while(status);
	return (0);
}
