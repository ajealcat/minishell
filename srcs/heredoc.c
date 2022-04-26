/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:56:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/26 18:31:25 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_here_doc(char *buffer, int fd_heredoc_in, int fd_heredoc_out)
{
	write(fd_heredoc_out, buffer, ft_strlen(buffer));
	close(fd_heredoc_out);
	fd_heredoc_in = open("objs/.heredoc", O_RDONLY);
	if (fd_heredoc_in < 0)
		return (FAILURE);
	return (fd_heredoc_in);
}

t_hdoc	*init_heredoc(char *eof)
{
	t_hdoc	*heredoc;

	heredoc = malloc(sizeof(t_hdoc));
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
	heredoc_in = heredoc->fd_heredoc_in;
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
	child_cmd = fork();
	secure_child(child_cmd);
	heredoc->fd_heredoc_out = open("objs/.heredoc", O_WRONLY \
		| O_CREAT | O_TRUNC, 0777);
	if (heredoc->fd_heredoc_out < 0)
		return (FAILURE);
	if (child_cmd == 0)
		boucle_line_heredoc(heredoc, multi, data);
	waitpid(child_cmd, 0, 0);
	// unlink("objs/.heredoc");
	return (free_heredoc(heredoc));
}
