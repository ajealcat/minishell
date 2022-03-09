/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:23:20 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/09 13:25:12 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unclose_quote(char *str)
{
	int check;

	check = check_quotes(str);
	if (check > 0)
	{
		if (check == 1)
			printf("Error simple quote\n");
		if (check == 2)
			printf("Error double quote\n");
	}
   // check = check_slash(str);
	return (0);
}
