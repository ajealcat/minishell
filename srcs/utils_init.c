/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:14:46 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/29 13:45:43 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**reduce_init_path2(t_token **tmp_list, t_path *our_path)
{
	int		i;
	char	*tmp;

	if (our_path == NULL)
		return (NULL);
	i = 0;
	while (*tmp_list && (*tmp_list)->type != T_PIPE
		&& our_path->my_path && our_path->my_path[i])
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
	return (our_path->my_path);
}

int	**reduce_init_pipex(t_pipex *multi)
{
	multi->fd = malloc(sizeof(int *) * (multi->count + 2));
	if (multi->fd == 0)
		return (NULL);
	multi->i = -1;
	while (++multi->i < (multi->count + 2))
		multi->fd[multi->i] = malloc(sizeof(int) * 2);
	multi->i = 0;
	while (multi->i < (multi->count + 2))
	{
		if (pipe(multi->fd[multi->i]) == -1)
			perror("Pipe");
		++multi->i;
	}
	return (multi->fd);
}

char	**my_path_slash(char **my_path, t_token *list)
{
	my_path = malloc(sizeof(char *) * 2);
	if (my_path == NULL)
		return (NULL);
	my_path[0] = ft_strdup(list->value);
	my_path[1] = NULL;
	return (my_path);
}

char	**my_path_dot(char **my_path, t_token *list)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	my_path = malloc(sizeof(char *) * 2);
	if (my_path == NULL)
		return (NULL);
	my_path[0] = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = my_path[0];
	my_path[0] = ft_strjoin(tmp, list->value);
	free(tmp);
	my_path[1] = NULL;
	return (my_path);
}

char	**my_path_current(t_path *our_path, t_token *list)
{
	char	*tmp;
	int		i;

	i = 0;
	while (our_path->my_path && our_path->my_path[i] && list && list->value)
	{
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], "/");
		free(tmp);
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], \
			list->value);
		free(tmp);
		i++;
	}
	return (our_path->my_path);
}
