/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:00:23 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/28 12:33:30 by ajearuth         ###   ########.fr       */
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

char	**create_arg2(t_token *list)
{
	t_token	*tmp;
	char	**av;
	int		count;

	tmp = list;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == VAR_WORD)
		{
			if (tmp->type == WORD && tmp->next && (tmp->next->type == D_QUOTE
					|| tmp->next->type == S_QUOTE))
				tmp->value = glue_value(tmp);
			count++;
		}
		tmp = tmp->next;
	}
	av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (NULL);
	tmp = list;
	av = reduce_create_arg2(tmp, av);
	return (av);
}

char	*glue_value(t_token *tmp)
{
	char	*dent;

	dent = tmp->value;
	tmp->value = ft_strjoin(tmp->value, tmp->next->value);
	free(dent);
	return (tmp->value);
}

char	**reduce_create_arg2(t_token *tmp, char **av)
{
	int	i;

	i = 0;
	while (tmp && (tmp->type == WORD || tmp->type == VAR_WORD))
	{
		av[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	av[i] = NULL;
	return (av);
}
