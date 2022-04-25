/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:44:10 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 16:47:23 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reduce_make_child_onecmd(t_pipex *multi, t_path *our_path)
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

void	wait_onecmd(pid_t child_cmd, t_pipex *multi, t_path *our_path)
{
	waitpid(child_cmd, 0, 0);
	free_multi(multi);
	free_our_path(our_path);
	g_status = 0;
}
