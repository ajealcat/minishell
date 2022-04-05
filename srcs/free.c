/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:00:34 by Fahima42          #+#    #+#             */
/*   Updated: 2022/04/05 16:54:37 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_our_path(t_path *our_path)
{
	if (our_path != NULL)
	{
		free_split(our_path->option_cmd);
		free_split(our_path->my_path);
	}
	free(our_path);
}

void	free_multi(t_pipex *multi)
{
	int	i;

	i = 0;
	while (i < multi->count + 2)
	{
		free(multi->fd[i]);
		i++;
	}
	free(multi->fd);
	free(multi);
}
