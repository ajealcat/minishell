/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:06:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/13 12:38:04 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_benv	*init_env(char **envp)
// {
// 	t_benv	*our_env;
// 	int		i;

// 	i = 0;
// 	our_env = malloc(sizeof(t_benv));
// 	if (!our_env)
// 		return (NULL);
// 	while (envp[i])
// 		i++;
// 	our_env->envp = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (envp[i])
// 	{
// 		our_env->envp[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	our_env->envp[i] = NULL;
// 	return (our_env);
// }
