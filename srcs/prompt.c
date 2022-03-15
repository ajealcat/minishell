/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/15 15:14:25 by Fahima42         ###   ########.fr       */
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
		// checker_red(list);
		while (list->next)
		{
			printf("token : | %d |\n value : | %s |\n", list->type, list->value);
			list = list->next;
		}
		printf("token : | %d |\n value : | %s |\n", list->type, list->value);
		// if (checker_red(list) != FAILURE)
		// 	free_list(&list);
		free(data->buf);
		free(data->str_trimed);
		free_list(&list);
	}
	return (SUCCESS);
}