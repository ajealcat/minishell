/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/04/25 17:09:49 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*parse(t_token *list, t_data *data)
{
	data->str_trimed = ft_strtrim(data->buf, " \t\n\r\f\v");
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
	while (tmp)
	{
		if (tmp->type == t_pipe)
			return (SUCCESS);
		tmp = tmp->next;
	}
	free(tmp);
	return (FAILURE);
}

int	parsing_for_exec(t_token *list, t_data *data)
{
	if (list && does_list_contain_pipe(list) == SUCCESS)
		make_exec_pipe(list, data);
	else if (list && does_list_contain_pipe(list) == FAILURE)
		make_exec_word(list, data);
	return (0);
}

int	parse_builtin(t_token *list, t_data *data, t_pipex *multi)
{
	if (ft_strncmp(list->value, "exit", 5) == 0)
		return (builtin_exit(list, data, multi));
	else if (ft_strncmp(list->value, "echo", 5) == 0)
		return (builtin_echo(list));
	else if (ft_strncmp(list->value, "pwd", 4) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(list->value, "cd", 3) == 0)
		return (builtin_cd(list));
	else if (ft_strncmp(list->value, "export", 7) == 0)
		return (builtin_export(list, data->our_env));
	else if (ft_strncmp(list->value, "unset", 6) == 0)
		return (builtin_unset(list, data->our_env));
	else if (ft_strncmp(list->value, "env", 4) == 0)
		return (builtin_env(data->our_env));
	return (FAILURE);
}
