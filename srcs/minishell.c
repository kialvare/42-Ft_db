/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:42:02 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/03 14:43:15 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

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
