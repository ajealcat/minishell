/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:54:02 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/27 15:56:50 by ajearuth         ###   ########.fr       */
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
	if (sig == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

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
		rl_replace_line("", 0);
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
