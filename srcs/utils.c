/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:14:51 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/21 09:47:57 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' '
		&& check_sep_for_word(str[i]) == SUCCESS)
		++i;
	return (i);
}

/* Pour savoir si le caractere spe est a ecrire et 
qu'il ne compte pas comme un token */

int	check_sep_for_word(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
		return (FAILURE);
	return (SUCCESS);
}

// pour lancer le parsing de word 

int	go_for_word(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"'
		|| c == '\t' || c == '\r' || c == '\n' || c == '\f'
		|| c == '\v' || c == ' ')
		return (FAILURE);
	return (SUCCESS);
}

int	ft_strlen_dollar(char *str)
{
	int	i;

	i = 1;
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
	{
		printf("str[i] = %c\n", str[i]);
		++i;
	}
	return (i);
}