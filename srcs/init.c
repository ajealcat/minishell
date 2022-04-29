/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:33:50 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/29 13:43:31 by ajearuth         ###   ########.fr       */
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

t_path	*init_path(t_env *our_env, t_token *list)
{
	t_path	*our_path;

	our_path = malloc(sizeof(t_path));
	if (!our_path)
		return (NULL);
	our_path->envp = our_env->envp;
	if (list && list->next && (list->type == L_RED || list->type == R_RED
			|| list->type == DL_RED || list->type == DR_RED))
		list = list->next->next;
	our_path->find_path = gojo_expand("PATH", our_env);
	our_path->option_cmd = get_option_cmd(list);
	our_path->my_path = NULL;
	if (list && list->value && list->value[0] == '\0')
		return (our_path);
	if (list && list->value && list->value[0] == '/')
		our_path->my_path = my_path_slash(our_path->my_path, list);
	else if (list && list->value && list->value[0] == '.')
		our_path->my_path = my_path_dot(our_path->my_path, list);
	else if (list != NULL)
	{
		our_path->my_path = ft_split((const char *)our_path->find_path, ':');
		our_path->my_path = my_path_current(our_path, list);
	}
	return (our_path);
}

t_path	*init_path2(t_env *our_env, t_token **tmp)
{
	t_path	*our_path;

	our_path = malloc(sizeof(t_path));
	if (!our_path)
		return (NULL);
	if (*tmp && (*tmp)->next && ((*tmp)->type == 1
			|| (*tmp)->type == 2 || (*tmp)->type == 3 || (*tmp)->type == 4))
		(*tmp) = (*tmp)->next->next;
	our_path->envp = our_env->envp;
	our_path->find_path = gojo_expand("PATH", our_env);
	our_path->option_cmd = get_option_cmd2(*tmp);
	our_path->my_path = NULL;
	if ((*tmp) && (*tmp)->value && (*tmp)->value[0] == '\0')
		return (our_path);
	if ((*tmp) && (*tmp)->value && (*tmp)->value[0] == '/')
		our_path->my_path = my_path_slash(our_path->my_path, (*tmp));
	else if ((*tmp) && (*tmp)->value && (*tmp)->value[0] == '.')
		our_path->my_path = my_path_dot(our_path->my_path, (*tmp));
	else if ((*tmp) != NULL)
	{
		our_path->my_path = ft_split((const char *)our_path->find_path, ':');
		our_path->my_path = reduce_init_path2(tmp, our_path);
	}
	increase_tmp_list(tmp);
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
	multi->list = list;
	multi->fd_file_out = 0;
	multi->fd_file_in = 0;
	multi->fd = reduce_init_pipex(multi);
	multi->i = 0;
	return (multi);
}
