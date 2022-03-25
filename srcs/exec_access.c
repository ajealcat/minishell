/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:45 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/25 17:17:24 by fboumell         ###   ########.fr       */
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
		printf("i : %d\n", i);
		if (!option_cmd)
			return (NULL);
		tmp = list;
		printf("j : %d\n", j);
		i = 0;
		while (tmp && tmp->type == word && (i < j))
		{
			option_cmd[i] = ft_strdup(tmp->value);
			printf("option cmd dans get : %s\n", option_cmd[i]);
			tmp = tmp->next;
			i++;
		}
	}
	return (option_cmd);
}

char	*find_path(t_token *list)
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
			printf("my_path : %s\n", my_path[i]);
			printf("option cmd : %s\n", option_cmd[0]);
			if (execve(my_path[i], option_cmd, &find_path) == -1)
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
