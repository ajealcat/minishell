/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:54:02 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/15 12:44:42 by ajearuth         ###   ########.fr       */
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
		// g_status = 130;
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		// g_status = 127;
		ft_putstr_fd("\b\b  \b\b  \b\b", 1);
	}
}
