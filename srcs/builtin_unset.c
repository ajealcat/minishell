/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:22:42 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/14 14:50:01 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_token *list, t_env *our_env)
{
	char	**tmp;
	char	**av;
	int		i;
	// int		j;
	// int		count;
	int		k;

	i = 1;
	// j = 0;
	k = 0;
	// count = 0;
	av = create_arg(list);
	tmp = NULL;
	// while (av[i])
	// {
	// 	if (is_var(our_env, av[i]) == SUCCESS)
	// 		count++;
	// 	i++;
	// }
	tmp = malloc(sizeof(char *) * ft_tablen(our_env->envp) + 2);
	if (!tmp)
		return (FAILURE);
	i = 1;
	if (count_av(av) > 1)
	{
		while (av[i])
		{
			tmp = unset_copy(our_env, tmp, av[i]);
			i++;
		}
	}
	free_split(our_env->envp);
	our_env->envp = tmp;
	free_split(av);
	free_split(tmp);
	return (SUCCESS);
}

char	**unset_copy(t_env *our_env, char **tmp, char *av)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (our_env->envp[k])
	{
		if (ft_strncmp(our_env->envp[k], av, ft_strlen(av)) == 0)
			k++;
		else
		{
			tmp[j] = ft_strdup(our_env->envp[k]);
			j++;
			k++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}
