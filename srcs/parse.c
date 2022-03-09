/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/09 16:34:11 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int parse(char *buf, t_data *data)
{
	int i;

	i = 0;
	data->token = ft_split(buf, ' ');
	while (data->token[i])
    {
       printf("%s\n", data->token[i]);
       i++;
    }
	while (data->token[i])
	{
		unclose_quote(data->token[i]);
		i++;
	}
   
    return (0);
}*/

int parse(t_data *data)
{
	data->token->str_trimed = ft_strtrim(data->buf, " \t\n\r\f\v");
//	printf("%s\n", data->token->str_trimed);
	check_category(data->token->str_trimed);
	
	return (0);
}

int	check_category(t_token *token)
{
	while (token->str_trimed[token->i])
	{
		if (token->str_trimed[token->i] == ' ')
			token->i++;
		else if (token->str_trimed[token->i] == '<')
			l_redirect(token);
		else if (token->str_trimed[token->i] == '>')
			r_redirect(token);
		else if (token->str_trimed[token->i] == '"')
			d_quote(token);
		else if (token->str_trimed[token->i] == '\'')
			s_quote(token);
		else if (ft_isalpha(token->str_trimed[token->i]) == 1)
			token_word(token);
		else if (token->str_trimed[token->i] == '|')
			token_pipe(token);
		else
			token->i++;
	}
	
}
