/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:45 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/05 16:48:48 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_option_cmd(t_token *list)
{
	t_token	*tmp;
	char	**option_cmd;
	int		i;
	int		j;

	tmp = list;
	i = 0;
	if (tmp == NULL || tmp->next == NULL)
	{
		option_cmd = malloc(sizeof(char *) * 2);
		if (!option_cmd)
			return (NULL);
		option_cmd[0] = ft_strdup(tmp->value);
		option_cmd[1] = NULL;
		return (option_cmd);
	}
	else
	{
		while (tmp->type == word && tmp->next != NULL)
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
		while (tmp && tmp->type == word && (i < j))
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
	while (tmp->type == word && tmp->next != NULL)
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
	while (tmp && tmp->type == word && (i < j))
	{
		option_cmd[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	option_cmd[i] = NULL;
	return (option_cmd);
}
