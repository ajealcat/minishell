/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_avalaible.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:07:03 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/10 18:45:51 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_left(t_token *token)
{
	if (token->type == l_red || token->type == dl_red)
	{
		if (token->prev != NULL && token->prev->type != word)
			return (FAILURE);
		if (token->next == NULL || token->next->type != word)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE); // securite si jamais on envoi un truc qui n'a rien a voir
}

int	is_valid_right(t_token *token)
{
	if (token->type == r_red || token->type == dr_red)
	{
		if (token->prev != NULL && token->prev->type != word)
			return (FAILURE);
		if (token->next == NULL || token->next->type != word)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	is_valid_t_pipe(t_token *token)
{
	if (token->type == t_pipe)
	{
		if (token->prev == NULL || token->prev->type != word)
			return (FAILURE);
		if (token->next == NULL || token->next->type != word)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}
