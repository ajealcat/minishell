/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:22:42 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/14 14:02:55 by fboumell         ###   ########.fr       */
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
	if (count_av(av) > 1)
	{
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
		count = 0;
		while (our_env->envp[k])
		{
			if (ft_strncmp(our_env->envp[k], av[i], (ft_strlen(av[i]) + 1)) != 0)
			{
				printf("strlen av : %lu\n", ft_strlen(av[i]));
				tmp[j] = ft_strdup(our_env->envp[k]);
				// printf("our_env : %s\n", our_env->envp[k]);
				j++;
				k++;
			}
			// if (ft_strncmp(our_env->envp[k], av[i], ft_strlen(av[i]) + 1) == 0)
			else
			{
				k++;
				printf("our_env s'il trouve : %s\n", our_env->envp[k]);
				i++;
			}
		}
	}
	tmp[j] = NULL;
	// int p = 0;
	// while (tmp[p])
	// {
	// 	printf("tmp : %s\n", tmp[p]);
	// 	p++;
	// }
	
	// free_split(our_env->envp);
	our_env->envp = tmp;
	free_split(av);
	free_split(tmp);
	return (SUCCESS);
}
