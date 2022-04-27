/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:59:38 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/27 15:56:45 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	ft_putstr_fd(heredoc->buffer, heredoc->fd[1]);
	free_heredoc(heredoc);
	free_exit(multi->list, data, 0, multi);
}
