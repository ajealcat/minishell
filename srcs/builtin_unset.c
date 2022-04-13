/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:22:42 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/13 17:57:17 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_token *list, t_env *our_env)
{
	char	**tmp;
	char	**av;
	char	**splited;
	int		i;
	int		count;

	i = 1;
	av = create_arg(list);
	tmp = NULL;
	if (count_av(av) > 1)
	{
		while (av[i])
		{
			splited = ft_split(av[i], '=');
			if (is_var(our_env, splited[0]) == SUCCESS)
				count++;
		}
		tmp = malloc(sizeof(char *) * (ft_tablen(our_env->envp) - count));
		if (!tmp)
			return (FAILURE);
		while (our_env->envp[i] && is_var(our_env, splited[0]) == FAILURE)
		{
			tmp[i] = ft_strdup(our_env->envp[i]);
			i++;
		}
	}
	free_split(av);
	return (SUCCESS);
}

int	is_var_unset(t_env *our_env, char *av)
{
	int		i;
	int		j;
	char	*tmp_str;
	char	**tmp;

	if (our_env->envp == NULL || av == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(our_env->envp)));
	i = 0;
	while (our_env->envp[i])
	{
		tmp[i] = ft_strdup(our_env->envp[i]);
		if (ft_strncmp(our_env->envp[i], av, ft_strlen(av)) == 0)
		{
			j = i;
			while (ft_strncmp(our_env->envp[j], av, ft_strlen(av)) == 0)
			{
				tmp_str = our_env->envp[j];
				our_env->envp[j] = our_env->envp[j + 1];
				our_env->envp[j + 1] = tmp_str;
				j++;
			}
		}
		i++;
	}
	our_env->envp[i - 1] = NULL;
	free (tmp_str);
	return (FAILURE);
}

char	**unset_value(t_env *our_env, char *av)
{
	char	**tmp;
	int		i;

	i = 0;
	if (our_env->envp == NULL || av == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(our_env->envp)));
	while (our_env->envp[i])
	{
		tmp[i] = ft_strdup(our_env->envp[i]);
		i++;
	}
	tmp[i + 1] = NULL;
	return (tmp);
}
