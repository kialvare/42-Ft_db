/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 08:05:28 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/26 10:06:27 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

#include "libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define	LNAME 16
#define	FNAME 16

typedef struct	s_field
{
	char			*header_name;
	void			*value;
	int				is_prime;
	int				is_foreign;
	struct s_field	*next;
}				t_fields;

typedef struct	 s_tree
{
	int				row;
	void			*value;
	struct s_tree	*next;
}				t_tree;

typedef struct	s_col
{
	char			*name;
	char			*type;
	int				count;
	int				min;
	int				max;
	int				sum;
	int				avg;
	t_tree			*data;
	struct s_col	*next;
}				t_col;

typedef struct	s_table
{
	t_col		*header;
	int			col_count;
	int			next_key;
	char		*primary_key;
	char		*foregin_key;
}				t_table;

int argc_len(char **argv);
int open_record(char *filename);
int open_record_delete(char *filename);
void close_record(int fd);
off_t find_record(int fd, char *key);
t_col *new_header(char *name);
t_col *lstadd_header(t_col *head, char *name);
t_tree *new_data(int row, char *value);
t_tree *lstadd_data(t_col *col, t_tree *head, int row, char *val);
t_table *build_table(int fd);
void print_table(t_table table);
t_fields *create_field(char *name);
t_fields *add_field(t_fields *head, char *col_name);
t_fields *build_record(t_table table);
void free_fields(t_fields *head);
int insert_record(int fd, t_fields *record);
void check_input(t_table table, char **input);
int handle_insert(int argc, char **argv);
int delete_record(int fd, char *key);
int handle_delete(int argc, char **argv);
char *scan_for_file(char *command, char **argv);
char **parse_col_list(char **argv);
int convert_to_index(int **colist_index, char **col_list, t_table *table);
int is_selected_column(int index, int *indexlist, int col_count);
int valid_column(char **col_list, t_table table);
void print_record(int fd, int *row_list, char **col_list, t_table table);
char **is_aggregate(char **col_list);
void print_aggregate(t_table *table, char **aggr_list);
int *select_record(char **col, t_table *table, char *Constraint);
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
t_table *build_table_constraint(int fd, char *constraint);
char **scan_for_file_multi(char *command, char **argv);
unsigned int assign_key(t_table table);
char **parse_values(char **values);
#endif
