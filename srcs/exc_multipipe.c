/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/31 17:15:03 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	make_exec_pipe(t_token *list, char **envp)
{
	t_token *tmp_list;
	pid_t	child_cmd;
	t_path	*our_path;
	int		count;
	int		i;
	int 	j;
	int		fd[2];
	i = 0;
	j = 0;
	tmp_list = list;
//	our_path = init_path(envp, tmp_list);
//	if (parse_builtin(list, list->value) == SUCCESS)
//		return (SUCCESS);
	// if (check_path(our_path) == FAILURE)
	// {
	// 	free_our_path(our_path);
	// 	return (FAILURE);
	// }
	count = how_much_pipe(list);
	pipe(fd);
	if (pipe(fd) == -1)
		perror("Pipe");
	while (i <= count)
	{
		our_path = init_path2(envp, &tmp_list);
		if (check_path(our_path) == FAILURE)
		{
			free_our_path(our_path);
			return (FAILURE);
		}
		child_cmd = fork();
		if (child_cmd < 0)
		{
			perror("Fork");
			return (FAILURE);
		}
		if (child_cmd == 0)
		{
			if (i == count)
			{
				if (dup2(fd[0], 0) == -1)
				{
					printf("ERROR\n");
					return (FAILURE);
				}
			}
			else if (i == 0)
				dup2(fd[1], 1);
			else
			{
				dup2(fd[0], 0);
				dup2(fd[1], 1);
			}
			close(fd[1]);
			close(fd[0]);
			cmd_execute(our_path);
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	while (j <= count)
	{
 		waitpid(child_cmd, 0, 0);
		j++;
	}
	free_our_path(our_path);
	return (0);
}


int	how_much_pipe(t_token *list)
{
	int			count;
	t_token		*tmp;

	count = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == t_pipe)
		{
			// pipe(tmp->pipefd);
			// if (pipe(pipefd) == -1)
			// {
			// 	perror("Pipe");
			// 	return (FAILURE);
			// }
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}
