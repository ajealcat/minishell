/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/30 18:33:52 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	how_much_pipe(t_token *list);

int	make_exec_pipe(t_token *list, char **envp)
{
	int		status;
	pid_t	child_cmd;
	t_path	*our_path;
	// int		pipefd[2];
	int		count;
	int		i;

	i = 0;
	our_path = init_path(envp, list);
//	if (parse_builtin(list, list->value) == SUCCESS)
//		return (SUCCESS);
	if (check_path(our_path) == FAILURE)
	{
		free_our_path(our_path);
		return (FAILURE);
	}
	// if (pipe(pipefd) == -1)
	// {
	// 	perror("Pipe");
	// 	return (FAILURE);
	// }
	count = how_much_pipe(list);
	while (i <= count)
	{
		our_path = init_path(envp, list);
		if (check_path(our_path) == FAILURE)
		{
			free_our_path(our_path);
			return (FAILURE);
		}
		child_cmd = fork();
		if (child_cmd < 0)
		{
			perror("Fork");
			return (FAILURE);
		}
		if (child_cmd == 0)
		{
			close(our_path->pipefd[0]);
			if (dup2(our_path->pipefd[1], 0) == -1)
				return (FAILURE);
			cmd_execute(our_path);
			while (list && list->type != t_pipe)
				list = list->next;
			list = list->next;
		}
		i++;
	}
	close(our_path->pipefd[1]);
	waitpid(child_cmd, &status, 0);
	// if (dup2(pipefd[0], 1) == -1)
	// 	return (FAILURE);
	free_our_path(our_path);
	return (0);
}

/* mettre les path dans un tableau de structures pour pouvoir acceder au fd precedent
a chaque creation de child */

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

/*
int	make_exec_pipe(t_token *list, char **envp)
{
	int			i;
	int			count;
	t_token		*tmp;

	i = 1;
	count = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == t_pipe)
			count++;
		tmp = tmp->next;
	}
	while (i <= count)
	{
		make_pipe(list, envp);
		while (list && list->type != t_pipe)
			list = list->next;
		list = list->next;
		i++;
	}
	make_last_child(list, envp);
	return (SUCCESS);
}

int	make_pipe(t_token *list, char **envp)
{
	pid_t	child_cmd;
	int		pipefd[2];
	t_path	*our_path;

	our_path = init_path(envp, list);
	// if (parse_builtin(list, list->value) == SUCCESS)
	// 	return (SUCCESS);
	if (check_path(our_path) == FAILURE)
	{
		free_our_path(our_path);
		return (FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		return (FAILURE);
	}
	child_cmd = fork();
	if (child_cmd < 0)
	{
		perror("Fork");
		return (FAILURE);
	}
	if (child_cmd == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
			return (FAILURE);
		cmd_execute(our_path);
	}
	else
	{
		close(pipefd[1]);
		waitpid(child_cmd, 0, 0);
		if (dup2(pipefd[0], 0) == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	make_last_child(t_token *list, char **envp)
{
	 pid_t	last_child;
	 int		pipefd[2];
	t_path	*our_path;

	our_path = init_path(envp, list);
	// if (parse_builtin(list, list->value) == SUCCESS)
	// 	return (SUCCESS);
	if (check_path(our_path) == FAILURE)
	{
		free_our_path(our_path);
		return (FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		return (FAILURE);
	}
	last_child = fork();
	if (last_child < 0)
	{
		perror("Fork");
		return (FAILURE);
	}
	if (last_child == 0)
	{
		close(pipefd[0]);
		cmd_execute(our_path);
	}
	else
	{
		waitpid(last_child, 0, 0);
		close(pipefd[1]);
	}
	return (SUCCESS);
}

*/