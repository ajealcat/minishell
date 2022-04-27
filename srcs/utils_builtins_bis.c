/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:00:23 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/27 18:02:56 by ajearuth         ###   ########.fr       */
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

int	is_builtin(t_token *list)
{
	if (!list)
		return (FAILURE);
	else if (ft_strncmp(list->value, "exit", 5) == 0)
		return (SUCCESS);
	else if (ft_strncmp(list->value, "echo", 5) == 0)
		return (SUCCESS);
	else if (ft_strncmp(list->value, "pwd", 4) == 0)
		return (SUCCESS);
	else if (ft_strncmp(list->value, "cd", 3) == 0)
		return (SUCCESS);
	else if (ft_strncmp(list->value, "export", 7) == 0)
		return (SUCCESS);
	else if (ft_strncmp(list->value, "unset", 6) == 0)
		return (SUCCESS);
	else if (ft_strncmp(list->value, "env", 4) == 0)
		return (SUCCESS);
	return (FAILURE);
}
