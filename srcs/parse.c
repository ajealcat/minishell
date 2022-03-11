/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/11 16:11:44 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int parse(t_data *data)
{
	printf("tu rentres?");
	data->token->str_trimed = ft_strtrim(data->buf, " \t\n\r\f\v");
	check_category(data->token);
	return (0);
}

int	check_category(t_token *token)
{
	while (token->str_trimed[token->i])
	{
		printf("??");
		if (token->str_trimed[token->i] == ' ')
			token->i++;
		else if (token->str_trimed[token->i] == '<')
			l_redirect(token);
		else if (token->str_trimed[token->i] == '>')
			r_redirect(token);
		else if (token->str_trimed[token->i] == '"')
			create_node("\"", d_quote);
		else if (token->str_trimed[token->i] == '\'')
			create_node("\'", s_quote);
		else if (ft_isalpha(token->str_trimed[token->i]) == 1)
			token_word(token);
		else if (token->str_trimed[token->i] == '|')
			create_node("|", t_pipe);
		else
			token->i++;
		printf("position : |%d| token : |%d|", token->str_trimed[token->i], token->type);
	}
	return (SUCCESS);
}
