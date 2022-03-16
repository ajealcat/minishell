/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/16 14:34:43 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_prompt(t_token *list, t_data *data)
{
	char *cmd;
	
	cmd = "exit";
	while (1)
	{
		init_data(data);
		data->buf = readline(PROMPT);
		if (data->buf != NULL)
			add_history(data->buf);
		if (ft_strncmp(data->buf, cmd, 5) == 0)
			exit(0);
		list = parse(list, data);
		// checker_red(list);
		// t_token *tmp;
		// tmp = list;
		// while (tmp->next)
		// {
		// 	printf("token : | %d |\n value : | %s |\n", tmp->type, tmp->value);
		// 	tmp = tmp->next;
		// }
		// printf("token : | %d |\n value : | %s |\n", tmp->type, tmp->value);
		if (list != NULL)
		{
			free(data->buf);
			free(data->str_trimed);
			free_list(&list);
		}
	}
	return (SUCCESS);
}