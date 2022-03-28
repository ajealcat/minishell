/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:45 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/28 14:34:06 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**get_option_cmd(t_token *list)
{
	t_token	*tmp;
	char	**option_cmd;
	int		i;
	int		j;

	tmp = list;
	i = 0;
	if (tmp->next == NULL)
	{
		option_cmd = malloc(sizeof(char *) * 2);
		if (!option_cmd)
			return (NULL);
		option_cmd[0] = ft_strdup(tmp->value);
		option_cmd[1] = NULL;
		return (option_cmd);
	}
	else
	{
		while (tmp->type == word && tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		i++;
		j = i;
		option_cmd = malloc(sizeof(char *) * (i + 1));
		if (!option_cmd)
			return (NULL);
		tmp = list;
		i = 0;
		while (tmp && tmp->type == word && (i < j))
		{
			option_cmd[i] = ft_strdup(tmp->value);
			tmp = tmp->next;
			i++;
		}
		option_cmd[i] = NULL;
	}
	return (option_cmd);
}

char	*find_path(t_token *list, char **envp)
{
	char	*find_path;
	char	**my_path;
	char	**option_cmd;
	int		i;

	find_path = getenv("PATH");
	my_path = ft_split(find_path, ':');
	option_cmd = get_option_cmd(list);
	i = 0;
	while (my_path[i])
	{
		my_path[i] = ft_strjoin(my_path[i], "/");
		my_path[i] = ft_strjoin(my_path[i], list->value);
		if (access(my_path[i], X_OK) == 0)
		{
			if (execve(my_path[i], option_cmd, envp) == -1)
				perror("Execve");
			free_split(option_cmd);
			return (my_path[i]);
		}
		i++;
	}
	free_split(my_path);
	free_split(option_cmd);
	return (0);
}
