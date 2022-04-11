/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/11 13:00:53 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_exec_pipe(t_token *list, char **envp, t_data *data)
{
	t_token		*tmp_list;
	pid_t		child_cmd;
	t_path		*our_path;
	t_pipex		*multi;

	tmp_list = list;
	if (parse_builtin(list, list->value, data) == SUCCESS)
		return (SUCCESS);
	multi = init_pipex(list);
	while (multi->i <= multi->count)
	{
		our_path = init_path2(envp, &tmp_list);
		if (check_path(our_path) == FAILURE)
			path_not_found(our_path);
		child_cmd = fork();
		secure_child(child_cmd);
		make_child(child_cmd, multi, our_path);
		free_our_path(our_path);
		multi->i++;
	}
	close_fd(multi->i, multi->count, multi->fd);
	while (multi->j <= multi->count)
	{
		waitpid(child_cmd, 0, 0);
		multi->j++;
	}
	free_multi(multi);
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
		if (tmp->type == t_pipe)
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

void	make_child(pid_t child_cmd, t_pipex *multi, t_path *our_path)
{
	if (child_cmd == 0)
	{
		if (multi->i == 0)
		{
			close_fd(multi->i, multi->count, multi->fd);
			dup2(multi->fd[multi->i + 1][1], 1);
		}
		else if (multi->i == multi->count)
		{
			close_fd(multi->i, multi->count, multi->fd);
			dup2(multi->fd[multi->i][0], 0);
		}
		else
		{
			close_fd(multi->i, multi->count, multi->fd);
			dup2(multi->fd[multi->i][0], 0);
			dup2(multi->fd[multi->i + 1][1], 1);
		}
		cmd_execute(our_path);
	}
}

t_token	*increase_tmp_list(t_token **tmp_list)
{
	while (*tmp_list && (*tmp_list)->type != t_pipe)
		*tmp_list = (*tmp_list)->next;
	if (*tmp_list && (*tmp_list)->type == t_pipe)
		*tmp_list = (*tmp_list)->next;
	return (*tmp_list);
}
