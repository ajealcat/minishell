/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:00:34 by Fahima42          #+#    #+#             */
/*   Updated: 2022/04/27 19:19:39 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_token **list)
{
	t_token	*tmp;
	t_token	*del;

	if (list != NULL && *list != NULL)
	{
		while ((*list) && (*list)->prev)
			(*list) = (*list)->prev;
		tmp = (*list);
		while (tmp != NULL)
		{
			del = tmp;
			if (tmp->value && (tmp->type == WORD || tmp->type == VAR_WORD))
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
	if (cmd == NULL)
		return ;
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
		free(our_path->find_path);
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

void	free_our_env(t_env *our_env)
{
	if (our_env->envp)
		free_split(our_env->envp);
	if (our_env->av)
		free_split(our_env->av);
	free(our_env);
}
