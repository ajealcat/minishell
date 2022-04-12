/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/12 12:40:39 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var(char **env, char *tmp)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}


void	replace_value(char **env, char **tmp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (env[i])
	{
		j = 0;
		if (ft_strncmp(env[i], tmp[0], ft_strlen(tmp[0])) == 0)
		{
			while (env[i][j] != '=')
				j++;
			k = 0;
			if (env[i][j] == '=')
			{
				j++;
				while (env[i][j])
				{
					while (tmp[1][k])
					{
						env[i][j] = tmp[1][k];
						k++;
						j++;
					}
					env[i][j] = '\0';
					j++;
				}
			}
		}
		i++;
	}
}

int	builtin_export(t_token *list, char **env)
{
	char	**tmp;
	char	**av;
	int		i;

	i = 1;
	av = create_arg(list);
	tmp = NULL;
	if (count_av(av) > 1)
	{
		while (av[i])
		{
			tmp = ft_split(av[i], '=');
			if (is_var(env, tmp[0]) == SUCCESS)
				replace_value(env, tmp);
			i++;
		}
	}
	free_split(av);
	free_split(tmp);
	return (SUCCESS);
}
