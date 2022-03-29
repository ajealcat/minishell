/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/29 12:49:40 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*parse(t_token *list, t_data *data)
{
	data->str_trimed = ft_strtrim(data->buf, " \t\n\r\f\v");
	if (unclose_quote(data->str_trimed) == FAILURE)
		return (NULL);
	list = check_category(list, data);
	return (list);
}

t_token	*check_category(t_token *list, t_data *data)
{
	while (data->str_trimed[data->i])
	{
		if (data->str_trimed[data->i] == ' ')
			data->i++;
		if (data->str_trimed[data->i] == '<')
			list = l_redirect(list, data);
		if (data->str_trimed[data->i] == '>')
			list = r_redirect(list, data);
		if (data->str_trimed[data->i] == '"')
			list = token_between_dquote(list, data);
		if (data->str_trimed[data->i] == '\'')
			list = token_between_squote(list, data);
		if (data->str_trimed[data->i] == '|')
			list = create_node(list, "|", t_pipe);
		if (data->str_trimed[data->i] == '$')
			list = token_dollar(list, data);
		else if (go_for_word(data->str_trimed[data->i]) == SUCCESS)
			list = token_word(list, data);
		data->i++;
	}
	return (list);
}

int	does_list_contain_pipe(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	printf("dans list contain pipe\n");
	while (tmp)
	{
		if (tmp->type == t_pipe)
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAILURE);
}

int	parsing_for_exec(t_token *list, char **envp)
{
/*	if (does_list_contain_pipe(list) == SUCCESS)
		make_exec_pipe(list, envp);
	else*/ 
	(void)envp;
	if (does_list_contain_pipe(list) == FAILURE)
		make_exec_word(list, envp);
//		printf("dans parsing for exec\n");
	return (0);
}
