/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/14 13:38:05 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var(t_env *our_env, char *tmp)
{
	int	i;

	i = 0;
	while (our_env->envp[i])
	{
		if (ft_strncmp(our_env->envp[i], tmp, ft_strlen(tmp)) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	replace_value(t_env *our_env, char **tmp)
{
	int	i;

	i = 0;
	while (our_env->envp[i])
	{
		if (ft_strncmp(our_env->envp[i], tmp[0], ft_strlen(tmp[0])) == 0)
			norm_export(tmp, our_env, i);
		i++;
	}
}

void	norm_export(char **tmp, t_env *our_env, int i)
{
	char	*tmp2;

	if (tmp == NULL || our_env->envp == NULL)
		return ;
	tmp2 = ft_strjoin(tmp[0], "=");
	free(our_env->envp[i]);
	if (tmp[1] == NULL)
		our_env->envp[i] = ft_strdup(tmp2);
	else
		our_env->envp[i] = ft_strjoin(tmp2, tmp[1]);
	free(tmp2);
}

char	**create_value(t_env *our_env, char *av)
{
	char	**tmp;
	int		i;

	i = 0;
	if (our_env->envp == NULL || av == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(our_env->envp) + 2));
	if (!tmp)
		return (NULL);
	while (our_env->envp[i])
	{
		tmp[i] = ft_strdup(our_env->envp[i]);
		i++;
	}
	tmp[i] = ft_strdup(av);
	tmp[i + 1] = NULL;
	return (tmp);
}

int	builtin_export(t_token *list, t_env *our_env)
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
			if (is_var(our_env, tmp[0]) == SUCCESS)
			{
				replace_value(our_env, tmp);
				free_split(tmp);
			}
			else
			{
				free_split(tmp);
				tmp = create_value(our_env, av[i]);
				free_split(our_env->envp);
				our_env->envp = tmp;
			}
			i++;
		}
	}
	free_split(av);
	return (SUCCESS);
}
