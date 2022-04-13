/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/13 12:36:22 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var(char **envp, char *tmp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tmp, ft_strlen(tmp)) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	replace_value(char **envp, char **tmp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tmp[0], ft_strlen(tmp[0])) == 0)
			norm_export(tmp, envp, i);
		i++;
	}
}

void	norm_export(char **tmp, char **envp, int i)
{
	int	j;
	int	k;

	j = 0;
	while (envp[i][j] != '=')
		j++;
	k = 0;
	if (envp[i][j] == '=')
	{
		j++;
		while (envp[i][j])
		{
			while (tmp[1][k])
			{
				envp[i][j] = tmp[1][k];
				k++;
				j++;
			}
			envp[i][j] = '\0';
			j++;
		}
	}
}

char	**create_value(char **envp, char **av)
{
	int		i;
	int		j;
	char	**tmp_str;

	i = 0;
	j = 1;
	while (envp[i])
		i++;
	tmp_str = malloc(sizeof(char *) * (i + (count_av(av) - 1)) + 1);
	i = 0;
	while (envp[i])
	{
		tmp_str[i] = ft_strdup(envp[i]);
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

int	builtin_export(t_token *list, char **envp)
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
			if (is_var(envp, tmp[0]) == SUCCESS)
				replace_value(envp, tmp);
			else
			{	
				tmp = create_value(envp, av);
				envp = tmp;
			}
			i++;
		}
	}
	free_split(av);
	free_split(tmp);
	return (SUCCESS);
}
