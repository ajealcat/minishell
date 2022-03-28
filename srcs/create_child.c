/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:30:26 by fboumell          #+#    #+#             */
/*   Updated: 2022/03/28 14:32:14 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_one_cmd(t_token *list, char **envp)
{
	int		status;
	pid_t	child_cmd;

	child_cmd = fork();
	secure_child(child_cmd);
	if (child_cmd == 0)
		find_path(list, envp);
	waitpid(child_cmd, &status, 0);
	return (status);
}
