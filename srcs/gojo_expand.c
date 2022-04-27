/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gojo_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:32:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/27 12:59:19 by ajearuth         ###   ########.fr       */
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
	char	*env;

	i = 0;
	while (our_env && our_env->envp && our_env->envp[i])
	{
		if (ft_strncmp(our_env->envp[i], tmp, ft_strlen(tmp)) == 0)
		{
			env = ft_strdup(our_env->envp[i] + (ft_strlen(tmp) + 1));
			return (env);
		}
		i++;
	}
	return (NULL);
}
