/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:46:48 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 14:47:08 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

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
