/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/11 18:11:57 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int parse(t_token *token)
{
	t_token *tmp;

	token->str_trimed = ft_strtrim(token->buf, " \t\n\r\f\v");
	tmp = check_category(token);
	
	return (0);
}

int	check_category(t_token *token)
{
	//printf("%d\n", token->i);
	int i;
	
	i = 0;
	while (token->str_trimed[i])
	{
		printf("str dans check category : |%c|\n", token->str_trimed[i]);
		if (token->str_trimed[i] == ' ')
			token->i++;
		if (token->str_trimed[i] == '<')
			l_redirect(token, i);
		if (token->str_trimed[i] == '>')
			r_redirect(token, i);
		if (token->str_trimed[i] == '"')
			create_node("\"", d_quote);
		if (token->str_trimed[i] == '\'')
			create_node("\'", s_quote);
		if (ft_isalpha(token->str_trimed[i]) == 1)
			token_word(token, i);
		if (token->str_trimed[i] == '|')
			create_node("|", t_pipe);
		i++;
		printf("str dans check category : |%c|\n", token->str_trimed[i]);
		printf("position : |%d| token : |%d|", token->str_trimed[i], token->type);
	}
	return (SUCCESS);
}
