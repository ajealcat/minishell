/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:00:34 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/28 15:14:17 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*double ** car la fontction doit directement effectuer //des modifications sur les objets de la liste*/

void	free_list(t_token **list)
{
	t_token	*tmp;
	t_token	*del;

	if (*list != NULL)
	{
		tmp = (*list);
		while (tmp != NULL)
		{
			del = tmp;
			if (tmp->type == word)
				free(tmp->value);
			tmp = tmp->next;
			free(del);
		}
		(*list) = NULL;
	}
}

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		++i;
	}
	free(cmd);
}
