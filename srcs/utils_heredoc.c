/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:59:38 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/28 21:45:02 by ajearuth         ###   ########.fr       */
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
	buffer_expand(heredoc, data);
	ft_putstr_fd(heredoc->buffer, heredoc->fd[1]);
	free_heredoc(heredoc);
	free_exit(multi->list, data, 0, multi);
}

static int	reduce_buffer_expand2(t_hdoc *heredoc, int count,
								char **tmp, int i)
{
	char	*tmp_buf;
	int		len;
	char	*tmp2;

	tmp2 = gojo_expand(*tmp, heredoc->data->our_env);
	free(*tmp);
	*tmp = ft_substr(heredoc->buffer, 0, i);
	len = ft_strlen(tmp2);
	if (tmp2)
	{
		tmp_buf = ft_strjoin(*tmp, tmp2);
		free(*tmp);
		free(tmp2);
	}
	else
		tmp_buf = *tmp;
	tmp2 = ft_substr(heredoc->buffer, i + count,
			ft_strlen(heredoc->buffer) - i - count);
	*tmp = ft_strjoin(tmp_buf, tmp2);
	free(tmp_buf);
	free(tmp2);
	free(heredoc->buffer);
	heredoc->buffer = *tmp;
	return (len);
}

static int	reduce_buffer_expand(t_hdoc *heredoc, int i)
{
	int		count;
	char	*tmp;

	count = 0;
	while (heredoc->buffer[i + count] != '\n'
		&& heredoc->buffer[i + count] != ' ')
		++count;
	tmp = ft_substr(heredoc->buffer, i + 1, count - 1);
	return (reduce_buffer_expand2(heredoc, count, &tmp, i));
}

void	buffer_expand(t_hdoc *heredoc, t_data *data)
{
	int		i;

	i = 0;
	heredoc->data = data;
	while (heredoc->buffer && heredoc->buffer[i])
	{
		if (heredoc->buffer[i] == '$')
			i += reduce_buffer_expand(heredoc, i);
		else
			++i;
	}
}
