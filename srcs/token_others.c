/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:57:17 by Fahima42          #+#    #+#             */
/*   Updated: 2022/04/26 16:57:32 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*r_redirect(t_token *list, t_data *data)
{
	if (ft_strncmp(data->str_trimed + data->i, ">>", 2) == 0)
	{
		list = create_node(list, ">>", DR_RED);
		data->i++;
	}
	else
		list = create_node(list, ">", R_RED);
	return (list);
}

t_token	*l_redirect(t_token *list, t_data *data)
{
	if (ft_strncmp(data->str_trimed + data->i, "<<", 2) == 0)
	{
		list = create_node(list, "<<", DL_RED);
		data->i++;
	}
	else
		list = create_node(list, "<", L_RED);
	return (list);
}

t_token	*token_word(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;

	size = ft_strlen_word(data->str_trimed + data->i);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (check_sep_for_word(data->str_trimed[data->i]) == 0 && j < size)
	{
		tmp[j] = data->str_trimed[data->i];
		data->i++;
		j++;
	}
	tmp[j] = '\0';
	list = create_node(list, tmp, WORD);
	data->i--;
	return (list);
}

t_token	*token_dollar(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;

	if (ft_strncmp(data->str_trimed + data->i, "$", 2) == 0)
		list = create_node(list, "$", VAR_WORD);
	size = ft_strlen_dollar(data->str_trimed + data->i);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (check_sep_for_word(data->str_trimed[data->i]) == SUCCESS
		&& j < (size - 1))
	{
		tmp[j] = data->str_trimed[data->i + 1];
		data->i++;
		j++;
	}
	tmp[j] = '\0';
	list = reduce_token_dollar(tmp, data, list);
	return (list);
}
