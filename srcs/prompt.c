/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/09 14:21:27 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_prompt(void)
{
	t_data data;
	char *cmd = "exit";

	while (1)
	{
		data.buf = readline(PROMPT);
	//	printf("buf : %s\n", buf);
		if (data.buf != NULL)
			add_history(data.buf);
		parse(&data);
		if (ft_strncmp(data.buf, cmd, 5) == 0)
			exit(0);
		free(data.buf);
	}
	return (0);
}