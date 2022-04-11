/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_onecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:30:26 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/11 12:59:55 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_exec_word(t_token *list, char **envp, t_data *data)
{
	int		status;
	pid_t	child_cmd;
	t_path	*our_path;

	if (parse_builtin(list, list->value, data) == SUCCESS)
		return (SUCCESS);
	our_path = init_path(envp, list);
	if (check_path(our_path) == FAILURE)
	{
		free_our_path(our_path);
		perror("Path");
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
	return (SUCCESS);
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
	