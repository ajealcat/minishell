/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_available.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:07:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/19 13:20:14 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checker_red(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == l_red || tmp->type == dl_red)
		{
			if (is_valid_left(tmp) == FAILURE)
				return (FAILURE);
		}
		else if (tmp->type == r_red || tmp->type == dr_red)
		{
			if (is_valid_right(tmp) == FAILURE)
				return (FAILURE);
		}
		else if (tmp->type == t_pipe)
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
		if (list->prev == NULL || (list->prev->type != word
			&& list->prev->type != var_word))
		{
			ft_putstr_fd("Syntax error pipe\n", 2);
			printf("c'estmoi\n");
			return (FAILURE);
		}
		if (list->next == NULL || (list->next->type != word
			&& list->next->type != var_word))
		{
			ft_putstr_fd("Syntax error pipe\n", 2);
			printf("non, c'estmoi\n");
			return (FAILURE);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
