/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_onecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:30:26 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/22 12:14:25 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_exec_word(t_token *list, t_data *data)
{
	int		status;
	pid_t	child_cmd;
	t_path	*our_path;
	t_pipex	*multi;

	multi = init_pipex(list);
	check_redirections(multi);
	if (set_up_fd(multi, data) == SUCCESS)
		return (SUCCESS);
	our_path = init_path(data->our_env, list);
	if (check_path(our_path) == FAILURE)
	{
		free_our_path(our_path);
		g_status = 127;
		perror("Path");
		return (FAILURE);
	}
	child_cmd = fork();
	secure_child(child_cmd);
	if (child_cmd == 0)
	{
		if (multi->fd_file_out != 0)
		{
			dup2(multi->fd_file_out, 1);
			close(multi->fd_file_out);
		}
		if (multi->fd_file_in != 0)
		{
			dup2(multi->fd_file_in, 0);
			close(multi->fd_file_in);
		}
		cmd_execute(our_path);
	}
	waitpid(child_cmd, &status, 0);
	free_multi(multi);
	free_our_path(our_path);
	g_status = 0;
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
	g_status = 127;
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
			if (execve(our_path->my_path[i], our_path->option_cmd, \
				our_path->envp) == -1)
			{
				free_our_path(our_path);
				g_status = 127;
				perror("Execve");
			}
		}
		++i;
	}
}

int	set_up_fd(t_pipex *multi, t_data *data)
{
	int	save_fdin;
	int	save_fdout;

	if (is_builtin(multi->list) == SUCCESS)
	{
		save_fdin = dup(0);
		save_fdout = dup(1);
		if (multi->fd_file_out != 0)
		{
			dup2(multi->fd_file_out, 1);
			close(multi->fd_file_out);
		}
		if (multi->fd_file_in != 0)
		{
			dup2(multi->fd_file_in, 0);
			close(multi->fd_file_in);
		}
		parse_builtin(multi->list, data, multi);
		if (multi->fd_file_out != 0)
		{
			dup2(save_fdout, 1);
			close(save_fdout);
		}
		if (multi->fd_file_in != 0)
		{
			dup2(save_fdin, 0);
			close(save_fdin);
		}
		free_multi(multi);
		return (SUCCESS);
	}
	return (FAILURE);
}
