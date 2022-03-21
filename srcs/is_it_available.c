/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_available.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:07:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/21 09:36:51 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_left(t_token *list)
{
	if (list->type == l_red || list->type == dl_red)
	{
		if (list->prev != NULL && list->prev->type != word)
		{
			ft_putstr_fd("Syntax error red_l\n", 2);
			return (FAILURE);
		}
		if (list->next == NULL || list->next->type != word)
		{
			ft_putstr_fd("Syntax error red_l\n", 2);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}

int	is_valid_right(t_token *list)
{
	if (list->type == r_red || list->type == dr_red)
	{
		if (list->prev != NULL && list->prev->type != word)
		{
			ft_putstr_fd("Syntax error red_r\n", 2);
			return (FAILURE);
		}
		if (list->next == NULL || list->next->type != word)
		{
			ft_putstr_fd("Syntax error red_r\n", 2);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}

int	is_valid_t_pipe(t_token *list)
{
	if (list->type == t_pipe)
	{
		if (list->prev == NULL || list->prev->type != word)
		{
			ft_putstr_fd("Syntax error pipe\n", 2);
			return (FAILURE);
		}
		if (list->next == NULL || list->next->type != word)
		{
			ft_putstr_fd("Syntax error pipe\n", 2);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
