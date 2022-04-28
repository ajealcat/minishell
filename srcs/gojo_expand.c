/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gojo_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:32:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 22:07:30 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*gojo_expand(char *tmp, t_env *our_env)
{
	char	*env;

	if (ft_strncmp(tmp, "?", 2) == 0)
		env = ft_itoa(g_status);
	else
		env = find_var(our_env, tmp);
	return (env);
}

char	*find_var(t_env *our_env, char *tmp)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	j = 0;
	while (our_env && our_env->envp && our_env->envp[i])
	{
		while (our_env->envp[i][j] != '=')
			j++;
		if ((j == (int)ft_strlen(tmp))
			&& ft_strncmp(our_env->envp[i], tmp, j) == 0)
		{
			env = ft_strdup(our_env->envp[i] + (ft_strlen(tmp) + 1));
			return (env);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
