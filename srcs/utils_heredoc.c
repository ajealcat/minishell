/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:59:38 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/26 18:27:10 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_sig(int sig)
{
	if (sig == HEREDOC_IGN)
	{
		signal(SIGSEGV, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == HEREDOC)
	{
		signal(SIGSEGV, heredoc_signaux);
		signal(SIGINT, heredoc_signaux);
		signal(SIGQUIT, heredoc_signaux);
	}
}

void	boucle_line_heredoc(t_hdoc *heredoc, t_pipex *multi, t_data *data)
{
	char	*tmp;

	check_sig(HEREDOC);
	heredoc->line = readline(">");
	while (heredoc->line)
	{
		if (strncmp(heredoc->line, heredoc->eof, ft_strlen(heredoc->eof)) == 0)
			break ;
		tmp = heredoc->buffer;
		heredoc->buffer = ft_strjoin(tmp, heredoc->line);
		free(tmp);
		free(heredoc->line);
		tmp = heredoc->buffer;
		heredoc->buffer = ft_strjoin(tmp, "\n");
		free(tmp);
		heredoc->line = readline(">");
	}
	heredoc->fd_heredoc_in = make_here_doc(heredoc->buffer, \
	heredoc->fd_heredoc_in, heredoc->fd_heredoc_out);
	// free(buffer);
	// free(line);
	 free_exit(multi->list, data, 0, multi);
}
