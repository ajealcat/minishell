/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 15:31:44 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data_buf(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	free_our_env(data->our_env);
	free(data);
	exit(0);
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		free(data->buf);
		free(data->str_trimed);
	}
}

int	print_prompt(t_data *data)
{
	t_token	*list;

	while (1)
	{
		list = NULL;
		init_data(data);
		signal(SIGINT, gestion_signaux);
		signal(SIGQUIT, gestion_signaux);
		data->buf = readline(PROMPT);
		if (!data->buf)
			free_data_buf(data);
		if (data->buf != NULL && ft_strlen(data->buf) != 0)
			add_history(data->buf);
		list = parse(list, data);
		if (checker_red(list) != FAILURE
			&& unclose_quote(data->str_trimed) != FAILURE)
			parsing_for_exec(list, data);
		free_data(data);
		free_list(&list);
	}
	return (SUCCESS);
}
