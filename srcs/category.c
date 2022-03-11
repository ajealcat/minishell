/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:57:17 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/11 15:54:07 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void r_redirect(t_token *token)
{
    if (token->str_trimed[token->i + 1] == '>')
        create_node(">>", dr_red);
	else
		create_node(">", r_red);
}

void l_redirect(t_token *token)
{
    if (token->str_trimed[token->i + 1] == '<')
        create_node("<<", dl_red);
	else
		create_node("<", l_red);
}

int token_word(t_token *token)
{
	int		size;
	int		j;
	char	*tmp;

    size = ft_strlen_space(token->str_trimed);
    tmp = malloc(sizeof(char) * size + 1);
	j = 0;
	while (ft_isalpha(token->str_trimed[token->i]) == 1)
	{
		tmp[j] = token->str_trimed[token->i];
		token->i++;
		j++;
	}
	tmp[j] = '\0';
	create_node(tmp, word); 
    return (0);
}