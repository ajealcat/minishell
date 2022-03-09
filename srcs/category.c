/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:57:17 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/09 17:18:25 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int dl_redirect(t_token *token)
{
    
}

int l_redirect(t_token *token)
{
    if (token->str_trimed[token->i + 1] == '<')
        dl_redirect(token->str_trimed[token->i + 1]);
	else
		
	//	token->type = l_red;
}

int token_word(t_token *token)
{
	int j;
    int i;
    int size;
	char *tmp;

    size = ft_strlen_space(token->str_trimed);
    tmp = malloc(sizeof(char) * size + 1);
	j = 0;
    i = 0;
	while (ft_isalpha(token->str_trimed[token->i]) == 1)
	{
		tmp[j] = token->str_trimed[token->i];
		token->i++;
		j++;
	}
	tmp[j] = '\0';
	create_node(tmp, word, token); 
    return (0);
}