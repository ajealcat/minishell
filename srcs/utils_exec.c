/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:54:57 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 16:12:47 by ajearuth         ###   ########.fr       */
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
