/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/11 16:15:51 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_prompt(void)
{
	t_data data;
	char *cmd = "exit";

	data = NULL;
	while (1)
	{
		data.buf = readline(PROMPT);
		if (data.buf != NULL)
			add_history(data.buf);
		printf("OK1\n");
		parse(&data);
		printf("OK2\n");
		if (ft_strncmp(data.buf, cmd, 5) == 0)
			exit(0);
		free(data.buf);
	}
	return (0);
}