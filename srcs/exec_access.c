/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:45 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/22 12:01:16 by ajearuth         ###   ########.fr       */
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
		while ((tmp->type == word || tmp->type == var_word) && tmp->next != NULL)
		{
			tmp = tmp->next;
			i++;
		}
		i++;
		j = i;
		option_cmd = malloc(sizeof(char *) * (i + 1));
		if (!option_cmd)
			return (NULL);
		tmp = list;
		i = 0;
		while (tmp && (tmp->type == word || tmp->type == var_word) && (i < j))
		{
			option_cmd[i] = ft_strdup(tmp->value);
			tmp = tmp->next;
			i++;
		}
		option_cmd[i] = NULL;
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
	while ((tmp->type == word || tmp->type == var_word) && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	i++;
	j = i;
	option_cmd = malloc(sizeof(char *) * (i + 1));
	if (!option_cmd)
		return (NULL);
	tmp = list;
	i = 0;
	while (tmp && (tmp->type == word || tmp->type == var_word) && (i < j))
	{
		option_cmd[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	option_cmd[i] = NULL;
	return (option_cmd);
}
