/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:56:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 15:50:43 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_hdoc	*init_heredoc(char *eof)
{
	t_hdoc	*heredoc;

	heredoc = malloc(sizeof(t_hdoc));
	if (heredoc == NULL)
		return (NULL);
	heredoc->fd_heredoc_out = 1;
	heredoc->fd_heredoc_in = 0;
	heredoc->buffer = ft_strdup("");
	heredoc->line = NULL;
	heredoc->eof = eof;
	return (heredoc);
}

int	free_heredoc(t_hdoc *heredoc)
{
	int	heredoc_in;

	if (heredoc == NULL)
		return (FAILURE);
	heredoc_in = heredoc->fd[0];
	if (heredoc->buffer)
		free(heredoc->buffer);
	if (heredoc->line)
		free(heredoc->line);
	free(heredoc);
	return (heredoc_in);
}

int	here_doc(char *eof, t_pipex *multi, t_data *data)
{
	t_hdoc	*heredoc;
	pid_t	child_cmd;

	heredoc = init_heredoc(eof);
	check_sig(HEREDOC_IGN);
	if (pipe(heredoc->fd) == -1)
		return (FAILURE);
	child_cmd = fork();
	secure_child(child_cmd);
	if (child_cmd == 0)
	{
		close(heredoc->fd[0]);
		boucle_line_heredoc(heredoc, multi, data);
	}
	close(heredoc->fd[1]);
	waitpid(child_cmd, 0, 0);
	return (free_heredoc(heredoc));
}
