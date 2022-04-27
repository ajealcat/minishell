/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:26:00 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/27 16:24:45 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	secure_child(pid_t child_cmd)
{
	if (child_cmd < 0)
	{
		perror("Fork");
		g_status = 127;
		return (1);
	}
	return (0);
}

int	path_not_found(t_path *our_path, t_pipex *multi)
{
	free_our_path(our_path);
	ft_putstr_fd("Error : Command not found\n", 2);
	if (multi)
		free_multi(multi);
	g_status = 127;
	return (FAILURE);
}

int	secure_fd(int fd)
{
	if (fd == -1)
	{
		perror("Open");
		g_status = 127;
	}
	return (FAILURE);
}
