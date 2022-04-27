/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:45 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/27 17:26:14 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**reduce_goc(t_token *list)
{
	char	**option_cmd;

	option_cmd = malloc(sizeof(char *) * 2);
	if (!option_cmd)
		return (NULL);
	option_cmd[0] = ft_strdup(list->value);
	option_cmd[1] = NULL;
	return (option_cmd);
}

char	**get_option_cmd(t_token *list)
{
	t_token	*tmp;
	char	**option_cmd;
	int		i;
	int		j;

	tmp = list;
	i = 0;
	if (tmp == NULL || tmp->next == NULL)
		option_cmd = reduce_goc(tmp);
	else
	{
		while ((tmp->type == WORD || tmp->type == VAR_WORD)
			&& tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		i++;
		j = i;
		option_cmd = reduce_goc_bis(tmp, list, i, j);
	}
	return (option_cmd);
}

char	**get_option_cmd2(t_token *list)
{
	t_token	*tmp;
	char	**option_cmd;
	int		i;
	int		j;

	tmp = list;
	i = 0;
	while ((tmp->type == WORD || tmp->type == VAR_WORD) && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	i++;
	j = i;
	option_cmd = reduce_goc_bis(tmp, list, i, j);
	return (option_cmd);
}

char	**reduce_goc_bis(t_token *tmp, t_token *list, int i, int j)
{
	char	**option_cmd;

	option_cmd = malloc(sizeof(char *) * (i + 1));
	if (!option_cmd)
		return (NULL);
	tmp = list;
	i = 0;
	while (tmp && (tmp->type == WORD || tmp->type == VAR_WORD) && (i < j))
	{
		option_cmd[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	option_cmd[i] = NULL;
	return (option_cmd);
}
