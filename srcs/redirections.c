/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:56:16 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/19 12:34:53 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == r_red || tmp->type == dr_red)
			return (SUCCESS);
		tmp = tmp->next;
	}
	free(tmp);
	return (FAILURE);
}


int	open_or_createfd(t_token *list)
{
	t_token	*tmp;
	int		i;
	int		fd1;
	int		fd2;

	i = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == r_red || tmp->type == dr_red)
			break ;
		tmp = tmp->next;
	}
	if (tmp && tmp->type == r_red && tmp->next == word)
	{
		tmp = tmp->next;
		fd1 = open(tmp->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd1 == -1)
		{
			perror("Open");
			g_status = 127;
			return (FAILURE);
		}
		return (fd1);
	}
	else if (tmp && tmp->type == dr_red && tmp->next == word)
	{
		tmp = tmp->next;
		fd2 = open(tmp->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd2 == -1)
		{
			perror("Open");
			g_status = 127;
			return (FAILURE);
		}
		return (fd2);
	}
	return (FAILURE);
}

