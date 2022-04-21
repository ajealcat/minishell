/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/21 15:08:13 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_exec_pipe(t_token *list, t_env *our_env, t_data *data)
{
	t_token		*tmp_list;
	pid_t		child_cmd;
	t_path		*our_path;
	t_pipex		*multi;

	tmp_list = list;
	multi = init_pipex(tmp_list);
	while (multi->i <= multi->count)
	{
		our_path = init_path2(our_env, &tmp_list);
		if (our_path == NULL)
			return (FAILURE);
		if (check_path(our_path) == FAILURE)
			path_not_found(our_path);
		check_redirections(multi);
		child_cmd = fork();
		secure_child(child_cmd);
		make_child(child_cmd, multi, our_path, data, our_env);
		multi->list = increase_tmp_list(&multi->list);
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
	g_status = 0;
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

void	make_child(pid_t child, t_pipex *multi, t_path *our_path, t_data *data, t_env *our_env)
{
	if (child == 0)
	{
		if (multi->i == 0)
		{
			close_fd(multi->i, multi->count, multi->fd);
			dup2(multi->fd[multi->i + 1][1], 1);
			close(multi->fd[multi->i + 1][1]);
			if (multi->fd_file_out != 0)
			{
				dup2(multi->fd_file_out, 1);
				close(multi->fd_file_out);
			}
			if (multi->fd_file_in != 0)
			{
				dup2(multi->fd_file_in, 0);
				close(multi->fd_file_in);
			}
		}
		else if (multi->i == multi->count)
		{
			close_fd(multi->i, multi->count, multi->fd);
			dup2(multi->fd[multi->i][0], 0);
			close(multi->fd[multi->i][0]);
			if (multi->fd_file_out != 0)
			{
				dup2(multi->fd_file_out, 1);
				close(multi->fd_file_out);
			}
			if (multi->fd_file_in != 0)
			{
				dup2(multi->fd_file_in, 0);
				close(multi->fd_file_in);
			}
		}
		else
		{
			close_fd(multi->i, multi->count, multi->fd);
			dup2(multi->fd[multi->i][0], 0);
			dup2(multi->fd[multi->i + 1][1], 1);
			close(multi->fd[multi->i + 1][1]);
			if (multi->fd_file_out != 0)
			{
				dup2(multi->fd_file_out, 1);
				close(multi->fd_file_out);
			}
			if (multi->fd_file_in != 0)
			{
				dup2(multi->fd_file_in, 0);
				close(multi->fd_file_in);
			}
		}
		if (parse_builtin(multi->list, data, our_env) == SUCCESS)
		{
			free_list(&multi->list);
			free_multi(multi);
			free_our_path(our_path);
			free_exit(NULL, data, 0, our_env);
		}
		else
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
