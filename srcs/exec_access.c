/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:45 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/25 15:42:28 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **get_path(t_token *list)
{
	t_token *tmp;

	tmp = list;
	while (tmp->type == word)
	{
		
		tmp = tmp->next;
	}
}

char	*find_path(t_token *list)
{
	char	*find_path;
	char	**my_path;
	int		i;

	find_path = getenv("PATH");
	my_path = ft_split(find_path, ':');
	i = 0;
	while (my_path[i])
	{
		my_path[i] = ft_strjoin(my_path[i], "/");
		my_path[i] = ft_strjoin(my_path[i], list->value);
		if (access(my_path[i], X_OK) == 0)
		{
			if (execve(my_path[i], list->value, envp) == -1)
				perror("Execve");
			free(find_path);
			return (my_path[i]);
		}
		i++;
	}
	free_split(my_path);
	free(find_path);
	return (0);
}
