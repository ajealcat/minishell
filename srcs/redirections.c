/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:56:16 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/20 13:01:15 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_pipex *multi)
{
	t_token	*tmp;
	int		fd;

	tmp = multi->list;
	fd = 0;
	while (tmp)
	{
		if (tmp->type == r_red)
		{
			if (tmp->next->type == word)
			{
				tmp = tmp->next;
				fd = open_or_createfd(tmp->value, 1);
			}
		}
		else if (tmp->type == dr_red)
		{
			if (tmp->next->type == word)
			{
				tmp = tmp->next;
				fd = open_or_createfd(tmp->value, 2);
			}
		}
		if (tmp && (tmp->next->type == t_pipe || tmp->next == NULL))
			multi->fd_file = fd;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	open_or_createfd(char *value, int nb)
{
	int		fd1;
	int		fd2;

	if (nb == 1)
	{
		fd1 = open(value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		secure_fd(fd1);
		return (fd1);
	}
	else if (nb == 2)
	{
		fd2 = open(value, O_CREAT | O_RDWR | O_APPEND, 0644);
		secure_fd(fd2);
		return (fd2);
	}
	return (FAILURE);
}
