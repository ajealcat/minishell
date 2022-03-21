/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:23:20 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/21 09:30:30 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unclose_quote(char *str)
{
	int	check;

	check = check_quotes(str);
	if (check > 0)
	{
		if (check == 1)
			printf("Error simple quote\n");
		if (check == 2)
			printf("Error double quote\n");
	}
	return (0);
}

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
