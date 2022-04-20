/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:00:23 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/20 17:02:54 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	(char **tmp, t_env *our_env, char *av, int i)
{
	free_split(tmp);
	tmp = create_value(our_env, av[i]);
	free_split(our_env->envp);
	our_env->envp = tmp;
}