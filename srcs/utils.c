/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:14:51 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/22 17:04:20 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Pour la longueur des mots sans quotes */

int	ft_strlen_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' '
		&& check_sep_for_word(str[i]) == SUCCESS)
		++i;
	return (i);
}

// Pour reparse dquote 

int	ft_strlen_encore(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		++i;
	return (i);
}
/* Pour la longueur des mots avec quotes*/

int	ft_strlen_between_quotes(char *str, int count, char quote)
{
	int	i;

	i = 0;
	while (str[i] && count > 0)
	{
		if (str[i] == quote)
			count--;
		i++;
	}
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
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		++i;
	return (i);
}
