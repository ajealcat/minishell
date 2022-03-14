/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/14 17:47:37 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_prompt(t_token *list, t_data *data)
{
	char *cmd;
	
	cmd = "exit";
	while (1)
	{
		data->buf = readline(PROMPT);
		if (data->buf != NULL)
			add_history(data->buf);
		if (ft_strncmp(data->buf, cmd, 5) == 0)
			exit(0);
		list = parse(list, data);
		while (list->next)
		{
			printf("token : | %d |\n value : | %s |\n", list->type, list->value);
			list = list->next;
		}
		printf("token : | %d |\n value : | %s |\n", list->type, list->value);
		free(data->buf);
	}
	return (0);
}