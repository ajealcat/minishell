/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:44:10 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/27 18:42:30 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reduce_make_child_onecmd(t_pipex *multi, t_path *our_path)
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
	if (cmd_execute(our_path) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	wait_onecmd(pid_t child_cmd, t_pipex *multi, t_path *our_path)
{
	int	status;

	waitpid(child_cmd, &status, 0);
	free_multi(multi);
	free_our_path(our_path);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = 128 + WTERMSIG(status);
}

void	reduce_setupfd(t_pipex *multi)
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
}

int	check_path_failed(t_path *our_path, t_pipex *multi)
{
	free_our_path(our_path);
	if (multi)
		free_multi(multi);
	g_status = 127;
	return (FAILURE);
}

int	exec_failed(t_pipex *multi, t_data *data, t_path *our_path)
{
	free_list(&multi->list);
	free_multi(multi);
	free_our_path(our_path);
	free_exit(NULL, data, 127, NULL);
	return (FAILURE);
}
