/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/17 16:58:36 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *parse(t_token *list, t_data *data)
{
	data->str_trimed = ft_strtrim(data->buf, " \t\n\r\f\v");
	list = check_category(list, data);
	return (list);
}

t_token	*check_category(t_token *list, t_data *data)
{
	while (data->str_trimed[data->i] && data->str_trimed[data->i] != '\0')
	{
		if (data->str_trimed[data->i] == ' ')
			data->i++;
		if (data->str_trimed[data->i] == '<')
			list = l_redirect(list, data);
		if (data->str_trimed[data->i] == '>')
			list = r_redirect(list, data);
		if (data->str_trimed[data->i] == '"')
			list = create_node(list, "\"", d_quote);
		if (data->str_trimed[data->i] == '\'')
			list = create_node(list, "\'", s_quote);
		if (data->str_trimed[data->i] == '|')
			list = create_node(list, "|", t_pipe);
		if (data->str_trimed[data->i] == '$')
			list = token_dollar(list, data);
		if (check_sep_for_word(data->str_trimed[data->i]) == SUCCESS)
		{
			list = token_word(list, data);
			data->i--;
		}
		data->i++;
	}
	return (list);
}
