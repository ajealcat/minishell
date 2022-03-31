/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/31 13:22:45 by ajearuth         ###   ########.fr       */
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

	i = 0;
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
	while (i <= count)
	{
		our_path = init_path(envp, tmp_list);
		printf(" ds exec pipe valeur tmp->list : [%s]\n", tmp_list->value);
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
			close(tmp_list->pipefd[0]);
			if (dup2(tmp_list->pipefd[1], 0) == -1)
				return (FAILURE);
			cmd_execute(our_path);
			while (tmp_list && tmp_list->type != t_pipe)
				tmp_list = tmp_list->next;
			tmp_list = tmp_list->next;
		}
		i++;
	}
	close(tmp_list->pipefd[1]);
	waitpid(child_cmd, 0, 0);
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
