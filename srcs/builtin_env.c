/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:33:22 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/13 13:34:01 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(char **our_env)
{
	int	i;
	int	j;

	i = 0;
	while (our_env[i])
	{
		j = 0;
		while (our_env[i][j])
		{
			ft_putchar_fd(our_env[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (SUCCESS);
}
