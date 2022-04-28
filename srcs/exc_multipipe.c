/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 14:07:56 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_exec_pipe(t_token *list, t_data *data)
{
	t_token		*tmp_list;
	pid_t		child_cmd;
	t_path		*our_path;
	t_pipex		*multi;

	tmp_list = list;
	multi = init_pipex(tmp_list);
	while (multi->i <= multi->count)
	{
		our_path = init_path2(data->our_env, &tmp_list);
		if (our_path == NULL)
			return (FAILURE);
		if (check_path(our_path) == -1 && is_builtin(multi->list) == -1)
			return (path_not_found(our_path, multi));
		reduce_vrreuumant(multi, data);
		child_cmd = fork();
		secure_child(child_cmd);
		if (make_child(child_cmd, multi, our_path, data) == FAILURE)
			return (FAILURE);
		multi->list = increase_tmp_list(&multi->list);
		free_our_path(our_path);
		multi->i++;
	}
	wait_exec_pipe(multi, child_cmd);
	return (0);
}

int	how_much_pipe(t_token *list)
{
	int			count;
	t_token		*tmp;

	count = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	close_fd(int i, int count, int **fd)
{
	int	j;

	j = 0;
	while (j < (count + 2))
	{
		if (i != j)
			close(fd[j][0]);
		if (i + 1 != j)
			close(fd[j][1]);
		j++;
	}
}

int	make_child(pid_t child, t_pipex *multi, t_path *our_path, t_data *data)
{
	if (child == 0)
	{
		check_sig(CHILD);
		if (multi->i == 0)
			reduce_make_child_one(multi);
		else if (multi->i == multi->count)
			reduce_make_child_two(multi);
		else
			reduce_make_child_three(multi);
		if (parse_builtin(multi->list, data, multi) == SUCCESS)
		{
			free_list(&multi->list);
			free_multi(multi);
			free_our_path(our_path);
			free_exit(NULL, data, 0, NULL);
		}
		if (cmd_execute(our_path) == FAILURE)
			return (exec_failed(multi, data, our_path));
	}
	return (SUCCESS);
}

t_token	*increase_tmp_list(t_token **tmp_list)
{
	while (*tmp_list && (*tmp_list)->type != T_PIPE)
		*tmp_list = (*tmp_list)->next;
	if (*tmp_list && (*tmp_list)->type == T_PIPE)
		*tmp_list = (*tmp_list)->next;
	return (*tmp_list);
}
