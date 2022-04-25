/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:56:16 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/25 17:25:28 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_pipex *multi, t_data *data)
{
	t_token	*tmp;
	int		fd_out;
	int		fd_in;

	tmp = multi->list;
	fd_out = 0;
	fd_in = 0;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type == R_RED)
		{
			if (tmp->next->type == WORD)
			{
				tmp = tmp->next;
				fd_out = open_or_createfd(tmp->value, 1);
			}
		}
		else if (tmp->type == L_RED)
		{
			if (tmp->next->type == WORD)
			{
				tmp = tmp->next;
				fd_in = open_or_createfd(tmp->value, 3);
			}
		}
		else if (tmp->type == DL_RED)
		{
			if (tmp->next->type == WORD)
			{
				tmp = tmp->next;
				fd_in = here_doc(tmp->value, multi, data);
			}
		}
		else if (tmp->type == DR_RED)
		{
			if (tmp->next->type == WORD)
			{
				tmp = tmp->next;
				fd_out = open_or_createfd(tmp->value, 2);
			}
		}
		if (tmp && (tmp->next == NULL || tmp->next->type == T_PIPE))
		{
			multi->fd_file_out = fd_out;
			multi->fd_file_in = fd_in;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	open_or_createfd(char *value, int nb)
{
	int		fd1;
	int		fd2;
	int		fd3;

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
	else if (nb == 3)
	{
		fd3 = open(value, O_RDONLY);
		secure_fd(fd3);
		return (fd3);
	}
	return (FAILURE);
}
