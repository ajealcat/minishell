/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/04 12:45:10 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	make_exec_pipe(t_token *list, char **envp)
{
	t_token *tmp_list;
	pid_t	child_cmd;
	t_path	*our_path;
	int		(*fd)[2];
	int		count;
	int		i;
	int 	j;
	int		k;

	i = 0;
	j = 0;
	tmp_list = list;
	count = how_much_pipe(list);
	fd = malloc(sizeof(int) * count);
	if (fd == 0)
		return (FAILURE);
	while (i < count)
	{
		pipe(fd[i]);
		if (pipe(fd[i]) == -1)
			perror("Pipe");
		++i;
	}
	i = 0;
	k = 0;
	while (i <= count)
	{
		our_path = init_path2(envp, &tmp_list);
		if (check_path(our_path) == FAILURE)
		{
			free_our_path(our_path);
			ft_putstr_fd("Command not found\n", 2);
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
				if (dup2(fd[k][0], 0) == -1)
				{
					printf("ERROR\n");
					return (FAILURE);
				}
			}
			else if (i == 0)
				dup2(fd[k][1], 1);
			else
			{
				dup2(fd[k][0], 0);
				dup2(fd[k][1], 1);
				k++;
			}
			close(fd[k][1]);
			close(fd[k][0]);
			cmd_execute(our_path);
		}
		i++;
	}
	close(fd[k][0]);
	close(fd[k][1]);
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
//			tmp->pipefd = malloc(sizeof(int) * 2);
//			pipe(tmp->pipefd);
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}
