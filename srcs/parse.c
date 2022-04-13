/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/04/13 14:37:03 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*parse(t_token *list, t_data *data)
{
	data->str_trimed = ft_strtrim(data->buf, " \t\n\r\f\v");
	// if (unclose_quote(data->str_trimed) == FAILURE)
	// 	return (NULL);
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

int	parsing_for_exec(t_token *list, t_env *our_env, t_data *data)
{
	if (list && does_list_contain_pipe(list) == SUCCESS)
		make_exec_pipe(list, our_env, data);
	else if (list && does_list_contain_pipe(list) == FAILURE)
		make_exec_word(list, our_env, data);
	return (0);
}


int	parse_builtin(t_token *list, char *value, t_data *data, t_env *our_env)
{
	if (ft_strncmp(value, "exit", 5) == 0)
		return (builtin_exit(list, data));
/*	else if (ft_strncmp(value, "$?", 3) == 0)
		return (other_cmd(list));*/
	else if (ft_strncmp(value, "echo", 5) == 0)
		return (builtin_echo(list));
	else if (ft_strncmp(value, "pwd", 4) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(value, "cd", 3) == 0)
		return (builtin_cd(list));
	else if (ft_strncmp(value, "export", 7) == 0)
		return (builtin_export(list, our_env));
/*	else if (ft_strncmp(value, "unset", 6) == 0)
		return (builtin_unset());*/
	else if (ft_strncmp(value, "env", 4) == 0)	
		return (builtin_env(our_env));
	return (FAILURE);
}
