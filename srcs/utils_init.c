/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:14:46 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/27 19:22:24 by ajearuth         ###   ########.fr       */
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
