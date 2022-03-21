/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:57:17 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/21 11:07:29 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*r_redirect(t_token *list, t_data *data)
{
	if (ft_strncmp(data->str_trimed + data->i, ">>", 2) == 0)
	{
		list = create_node(list, ">>", dr_red);
		data->i++;
	}
	else
		list = create_node(list, ">", r_red);
	return (list);
}

t_token	*l_redirect(t_token *list, t_data *data)
{
	if (ft_strncmp(data->str_trimed + data->i, "<<", 2) == 0)
	{
		list = create_node(list, "<<", dl_red);
		data->i++;
	}
	else
		list = create_node(list, "<", l_red);
	return (list);
}

t_token	*token_word(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;

	size = ft_strlen_space(data->str_trimed + data->i);
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
	list = create_node(list, tmp, word);
	return (list);
}

t_token	*token_dollar(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;

	size = ft_strlen_dollar(data->str_trimed + data->i);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (check_sep_for_word(data->str_trimed[data->i]) == SUCCESS && j < size)
	{
		tmp[j] = data->str_trimed[data->i];
		data->i++;
		j++;
	}
	tmp[j] = '\0';
	printf("dans token word i = %d\n", data->i);
	list = create_node(list, tmp, var);
	return (list);
}
