/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:31:05 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 14:56:44 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

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
