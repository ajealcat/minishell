/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:22:42 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/14 14:23:35 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_token *list, t_env *our_env)
{
	char	**tmp;
	char	**av;
	int		i;
	int		j;
	int		count;
	int		k;

	i = 1;
	j = 0;
	k = 0;
	count = 0;
	av = create_arg(list);
	tmp = NULL;
	while (av[i])
	{
		if (is_var(our_env, av[i]) == SUCCESS)
			count++;
		i++;
	}
	tmp = malloc(sizeof(char *) * (ft_tablen(our_env->envp) - count + 2));
	if (!tmp)
		return (FAILURE);
	i = 1;
	if (count_av(av) > 1)
	{
		while (our_env->envp[k])
		{
			if (ft_strncmp(our_env->envp[k], av[i], (ft_strlen(av[i]))) == 0)
				k++;
			tmp[j] = ft_strdup(our_env->envp[k]);
			j++;
			k++;
		}
		i++;
	}
	tmp[j] = NULL;
	// free_split(our_env->envp);
	our_env->envp = tmp;
	free_split(av);
	free_split(tmp);
	return (SUCCESS);
}
