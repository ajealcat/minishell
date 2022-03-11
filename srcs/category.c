/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:57:17 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/11 18:40:03 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int r_redirect(t_token *token, int i)
{
    if (token->str_trimed[i + 1] == '>')
        create_node(">>", dr_red);
	else
		create_node(">", r_red);
	return (i);
}

int l_redirect(t_token *token, int i)
{
    if (token->str_trimed[i + 1] == '<')
        create_node("<<", dl_red);
	else
		create_node("<", l_red);
	return (i);
}

int token_word(t_token *token, int i)
{
	int		size;
	int		j;
	char	*tmp;

    size = ft_strlen_space(token->str_trimed);
    tmp = malloc(sizeof(char) * size + 1);
	j = 0;
	while (ft_isalpha(token->str_trimed[i]) == 1)
	{
		tmp[j] = token->str_trimed[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	create_node(token, tmp, word); 
    return (i);
}