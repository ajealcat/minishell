/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:33:50 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/29 12:48:19 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_token *list)
{
	list->type = 0;
	list->value = NULL;
	list->next = NULL;
	list->prev = NULL;
}

void	init_data(t_data *data)
{
	data->buf = NULL;
	data->str_trimed = NULL;
	data->i = 0;
}

t_path	*init_path(char **envp, t_token *list)
{
	t_path	*our_path;
	int		i;

	i = 0;
	our_path = malloc(sizeof(t_path));
	if (!our_path)
		return (NULL);
	our_path->envp = envp;
	our_path->find_path = getenv("PATH");
	our_path->option_cmd = get_option_cmd(list);
	our_path->my_path = ft_split((const char *)our_path->find_path, ':');
	while (our_path->my_path[i])
	{
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], "/");
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], list->value);
		i++;
	}
	return (our_path);
}
