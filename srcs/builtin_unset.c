/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:22:42 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/15 14:26:22 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_token *list, t_env *our_env)
{
	char	**to_free;
	char	**av;
	int		i;
	int		count;

	av = create_arg(list);
	i = 1;
	count = 0;
	while (our_env && our_env->envp && av && av[i])
	{
		if (is_var(our_env, av[i]) == SUCCESS)
			count++;
		i++;
	}
	if (count == 0)
	{
		free_split(av);
		return (SUCCESS);
	}
	to_free = our_env->envp;
	our_env->envp = unset_copy(our_env, av, count);
	free_split(to_free);
	free_split(av);
	g_status = 0;
	return (SUCCESS);
}

/*
Renvoie SUCCESS si la variable d'environment fait partie
des arguments donnés, FAILURE sinon.
*/
int	is_argument(char **av, char *env_var)
{
	int	i;

	i = 0;
	while (env_var && av && av[i])
	{
		if (ft_strncmp(av[i], env_var, ft_strlen(av[i])) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	**unset_copy(t_env *our_env, char **av, int count)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char *) * (ft_tablen(our_env->envp) - count + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (our_env->envp[i])
	{
		if (count && is_argument(av, our_env->envp[i]) == SUCCESS)
		{
			++i;
			--count;
		}
		else
			tmp[j++] = ft_strdup(our_env->envp[i++]);
	}
	tmp[j] = NULL;
	return (tmp);
}
