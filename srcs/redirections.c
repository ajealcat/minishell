/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:56:16 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/19 15:13:35 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == r_red)
		{
			if (tmp->next->type == word)
			{
				tmp = tmp->next;
				open_or_createfd(tmp->value, 1);
			}
		}
		else if (tmp->type == dr_red)
		{
			if (tmp->next->type == word)
			{
				tmp = tmp->next;
				open_or_createfd(tmp->value, 2);
			}
		}
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
		if (fd1 == -1)
		{
			perror("Open");
			g_status = 127;
			return (FAILURE);
		}
	}
	else if (nb == 2)
	{
		fd2 = open(value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd2 == -1)
		{
			perror("Open");
			g_status = 127;
			return (FAILURE);
		}
	}
	return (FAILURE);
}

