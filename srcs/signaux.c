/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:54:02 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/25 15:48:58 by ajearuth         ###   ########.fr       */
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

	// if (sig == SIGINT)
	// {

	// 	ft_putstr_fd("\n", 0);
	// 	rl_replace_line("", 0);
	// 	g_status = 130;
	// 	write(1, "\n", 1);
	// 	// rl_replace_line("", 0);
	// 	close(STDIN_FILENO);
	// }
	// if (sig == SIGQUIT)
	// {
	// 	g_status = 127;
	// 	rl_replace_line("", 0);
	// }
	if (sig == SIGSEGV)
	{
		printf("\n");
		exit(0);
	}
}
