/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protection_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:11:35 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/21 09:43:58 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// nombre impair mais derniere c'et une double quote qui est entre single quote
// single quote idem
// "'" ou '\'' --> a afficher si echo

int	check_quotes(char *token)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (token[i])
	{
		if (token[i] == '\'')
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
		}
		if (token[i] == '"')
		{
			if (quote == 0)
				quote = 2;
			else if (quote == 2)
				quote = 0;
		}
		i++;
	}
	return (quote);
}
