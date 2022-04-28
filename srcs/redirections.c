/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:56:16 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/28 14:53:15 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reduce_check_red(t_token *tmp, t_pipex *multi, t_data *data, int value)
{
	int		fd;

	fd = 0;
	if (value == 4)
	{
		if (tmp->next->type == WORD)
		{
			tmp = tmp->next;
			fd = here_doc(tmp->value, multi, data);
			return (fd);
		}
	}
	if (tmp->next->type == WORD)
	{
		tmp = tmp->next;
		fd = open_or_createfd(tmp->value, value);
		return (fd);
	}
	return (FAILURE);
}

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
			fd_out = reduce_check_red(tmp, NULL, NULL, 1);
		else if (tmp->type == L_RED)
			fd_in = reduce_check_red(tmp, NULL, NULL, 3);
		else if (tmp->type == DL_RED)
			fd_in = reduce_check_red(tmp, multi, data, 4);
		else if (tmp->type == DR_RED)
			fd_out = reduce_check_red(tmp, NULL, NULL, 2);
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
