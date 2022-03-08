/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/08 13:28:04 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_prompt(void)
{
	t_data data;
	char *buf;
	char *cmd = "exit";

	while (1)
	{
		buf = readline(PROMPT);
	//	printf("buf : %s\n", buf);
		if (buf != NULL)
			add_history(buf);
		parse(buf, &data);
		if (ft_strncmp(buf, cmd, 5) == 0)
			exit(0);
		free(buf);
	}
	return (0);
}