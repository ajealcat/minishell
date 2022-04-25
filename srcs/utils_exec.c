/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:54:57 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 16:18:16 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_exec_pipe(t_pipex *multi, pid_t child_cmd)
{
	while (multi->j <= multi->count)
	{
		waitpid(child_cmd, 0, 0);
		multi->j++;
	}
	free_multi(multi);
	g_status = 0;
}

void	reduce_make_child_one(t_pipex *multi)
{
	close_fd(multi->i, multi->count, multi->fd);
	dup2(multi->fd[multi->i + 1][1], 1);
	close(multi->fd[multi->i + 1][1]);
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

void	reduce_make_child_two(t_pipex *multi)
{
	close_fd(multi->i, multi->count, multi->fd);
	dup2(multi->fd[multi->i][0], 0);
	close(multi->fd[multi->i][0]);
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

void	reduce_make_child_three(t_pipex *multi)
{
	close_fd(multi->i, multi->count, multi->fd);
	dup2(multi->fd[multi->i][0], 0);
	dup2(multi->fd[multi->i + 1][1], 1);
	close(multi->fd[multi->i + 1][1]);
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
