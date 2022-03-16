/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:14 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/16 16:30:00 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_token *list;
	t_data *data;
	
	list = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		message_error(list, data);
	if (data == NULL)
		return(0);
	if (ac || av)
	{
		// init_data(data);
		print_prompt(list, data);
	}
	return(0);
}
