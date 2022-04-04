/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_onecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:30:26 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/04 11:57:11 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_exec_word(t_token *list, char **envp)
{
	int		status;
	pid_t	child_cmd;
	t_path	*our_path;

	our_path = init_path(envp, list);
//	if (parse_builtin(list, list->value) == SUCCESS)
//		return (SUCCESS);
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
		cmd_execute(our_path);
	waitpid(child_cmd, &status, 0);
	free_our_path(our_path);
	return (0);
}

int	check_path(t_path *our_path)
{
	int	i;

	i = 0;
	while (our_path->my_path[i])
	{
		if (access(our_path->my_path[i], X_OK) == 0)
			return (SUCCESS);
		++i;
	}
	return (FAILURE);
}

void	cmd_execute(t_path *our_path)
{
	int	i;

	i = 0;
	while (our_path->my_path[i])
	{
		if (access(our_path->my_path[i], X_OK) == 0)
		{
			if (execve(our_path->my_path[i], our_path->option_cmd, our_path->envp) == -1)
			{
				free_our_path(our_path);
				perror("Execve");
			}
		}
		++i;
	}
}
	