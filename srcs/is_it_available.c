/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_available.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:07:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 17:29:09 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checker_red(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == L_RED || tmp->type == DL_RED)
		{
			if (is_valid_left(tmp) == FAILURE)
				return (FAILURE);
		}
		else if (tmp->type == R_RED || tmp->type == DR_RED)
		{
			if (is_valid_right(tmp) == FAILURE)
				return (FAILURE);
		}
		else if (tmp->type == T_PIPE)
		{
			if (is_valid_t_pipe(tmp) == FAILURE)
				return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	is_valid_left(t_token *list)
{
	if (list->type == L_RED || list->type == DL_RED)
	{
		if (list->prev != NULL && list->prev->type != WORD)
		{
			ft_putstr_fd("Syntax error red_l\n", 2);
			return (FAILURE);
		}
		if (list->next == NULL || list->next->type != WORD)
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
	if (list->type == R_RED || list->type == DR_RED)
	{
		if (list->prev != NULL && list->prev->type != WORD)
		{
			ft_putstr_fd("Syntax error red_r\n", 2);
			return (FAILURE);
		}
		if (list->next == NULL || list->next->type != WORD)
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
	if (list->type == T_PIPE)
	{
		if (list->prev == NULL || (list->prev->type != WORD
				&& list->prev->type != VAR_WORD))
		{
			ft_putstr_fd("Syntax error pipe\n", 2);
			return (FAILURE);
		}
		if (list->next == NULL || (list->next->type != WORD
				&& list->next->type != VAR_WORD))
		{
			ft_putstr_fd("Syntax error pipe\n", 2);
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
