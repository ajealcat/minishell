/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_available.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:07:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/15 13:11:43 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_left(t_token *list)
{
	if (list->type == l_red || list->type == dl_red)
	{
		if (list->prev != NULL && list->prev->type != word)
			return (FAILURE);
		if (list->next == NULL || list->next->type != word)
			return (FAILURE);
		// return (SUCCESS);
	}
	return (SUCCESS); // securite si jamais on envoi un truc qui n'a rien a voir
}

int	is_valid_right(t_token *list)
{
	if (list->type == r_red || list->type == dr_red)
	{
		if (list->prev != NULL && list->prev->type != word)
			return (FAILURE);
		if (list->next == NULL || list->next->type != word)
			return (FAILURE);
		// return (SUCCESS);
	}
	return (SUCCESS);
}

int	is_valid_t_pipe(t_token *list)
{
	if (list->type == t_pipe)
	{
		if (list->prev == NULL || list->prev->type != word)
			return (FAILURE);
		if (list->next == NULL || list->next->type != word)
			return (FAILURE);
		else
			return (SUCCESS);
	}
	return (FAILURE);
}
