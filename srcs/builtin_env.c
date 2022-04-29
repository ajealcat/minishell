/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:33:22 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/29 13:38:07 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_env *our_env)
{
	int	i;
	int	j;

	i = 0;
	while (our_env->envp[i])
	{
		j = 0;
		while (our_env->envp[i][j])
		{
			ft_putchar_fd(our_env->envp[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	g_status = 0;
	return (SUCCESS);
}
