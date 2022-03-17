/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:14:51 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/17 17:24:30 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strlen_space(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != ' ' 
		&& check_sep_for_word(str[i]) == SUCCESS)
        ++i;
    return (i);
}

// Pour savoir si le caractere spe est a ecrire et qu'il ne compte pas comme un token

int check_sep_for_word(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
		return (FAILURE);
	return (SUCCESS);
}

int ft_strlen_dollar(char *str)
{
    int i;

    i = 1;
    while (ft_isalnum(str[i]) == 1 || str[i] == '_')
	{
		printf("str[i] = %c\n", str[i]);
        ++i;
	}
	return (i);
}