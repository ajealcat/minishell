/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/12 16:32:55 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var(t_benv *env, char *tmp)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], tmp, ft_strlen(tmp)) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	replace_value(t_benv *env, char **tmp)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], tmp[0], ft_strlen(tmp[0])) == 0)
			norm_export(tmp, env, i);
		i++;
	}
}


void	norm_export(char **tmp, t_benv *env, int i)
{
	int	j;
	int	k;

	j = 0;
	while (env->envp[i][j] != '=')
		j++;
	k = 0;
	if (env->envp[i][j] == '=')
	{
		j++;
		while (env->envp[i][j])
		{
			while (tmp[1][k])
			{
				env->envp[i][j] = tmp[1][k];
				k++;
				j++;
			}
			env->envp[i][j] = '\0';
			j++;
		}
	}
}

char	**create_value(t_benv *env, char **av)
{
	int		i;
	int		j;
	char	**tmp_str;

	i = 0;
	j = 1;
	while (env->envp[i])
		i++;
	tmp_str = malloc(sizeof(char *) * (i + (count_av(av) - 1)) + 1);
	i = 0;
	while (env->envp[i])
	{
		tmp_str[i] = ft_strdup(env->envp[i]);
		i++;
	}
	while (av[j])
	{
		tmp_str[i] = ft_strdup(av[j]);
		j++;
		i++;
	}
	tmp_str[i] = NULL;
	return (tmp_str);
}

int	builtin_export(t_token *list, t_benv *env)
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
			else
			{	
				create_value(env, av);
				env->envp = tmp;
			}
			i++;
		}
	}
	free_split(av);
	free_split(tmp);
	return (SUCCESS);
}
