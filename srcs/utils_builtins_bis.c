/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:00:23 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/20 17:15:26 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reduce_builtexport(char **tmp, t_env *our_env, char *av)
{
	free_split(tmp);
	tmp = create_value(our_env, av);
	free_split(our_env->envp);
	our_env->envp = tmp;
}
