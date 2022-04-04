/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:33:50 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/04 17:10:24 by ajearuth         ###   ########.fr       */
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
	char	*tmp;
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
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], "/");
		free(tmp);
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], list->value);
		free(tmp);
		i++;
	}
	return (our_path);
}

t_path	*init_path2(char **envp, t_token **tmp_list)
{
	t_path	*our_path;
	char	*tmp;
	int		i;

	i = 0;
	our_path = malloc(sizeof(t_path));
	if (!our_path)
		return (NULL);
	our_path->envp = envp;
	our_path->find_path = getenv("PATH");
	our_path->option_cmd = get_option_cmd(*tmp_list);
	our_path->my_path = ft_split((const char *)our_path->find_path, ':');
	while (*tmp_list && (*tmp_list)->type != t_pipe && our_path->my_path[i])
	{
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], "/");
		free(tmp);
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], \
			(*tmp_list)->value);
		free(tmp);
		i++;
	}
	increase_tmp_list(tmp_list);
	return (our_path);
}

t_pipex	*init_pipex(t_token *list)
{
	t_pipex	*multi;

	multi = malloc(sizeof(t_pipex));
	if (!multi)
		return (NULL);
	multi->i = 0;
	multi->j = 0;
	multi->count = how_much_pipe(list);
	multi->fd = malloc(sizeof(int *) * (multi->count + 2));
	if (multi->fd == 0)
		return (NULL);
	multi->i = -1;
	while (++multi->i < (multi->count + 2))
		multi->fd[multi->i] = malloc(sizeof(int) * 2);
	multi->i = 0;
	while (multi->i < (multi->count + 2))
	{
		pipe(multi->fd[multi->i]);
		if (pipe(multi->fd[multi->i]) == -1)
			perror("Pipe");
		++multi->i;
	}
	multi->i = 0;
	return (multi);
}
