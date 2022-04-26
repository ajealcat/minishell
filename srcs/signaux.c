/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:54:02 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/26 12:59:27 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gestion_signaux(int sig)
{
	char	*str_null;

	str_null = NULL;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		g_status = 130;
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_status = 127;
		ft_putstr_fd("\b\b  \b\b  \b\b", 1);
	}
}

void	heredoc_signaux(int sig)
{

	if (sig == SIGINT)
	{

		write(1, "\n", 1);
		close(STDIN_FILENO);
		g_status = 130;
	}
	else if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
	else if (sig == SIGSEGV)
	{
		printf("\n");
		exit(0);
	}
}
