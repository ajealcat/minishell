/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:03:52 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/11 17:22:32 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void  init_token(t_token *token)
{
    token->buf = NULL;
    token->str_trimed = NULL;
	printf("inittoken\n");
	fflush(stdout);
 //   token->i = 0;
 //   return(*token);
}

void	init_list(dblist *list)
{
	list->head = NULL;
	list->tail = NULL;
}
/*
void init_data(t_data *data)
{
    data->buf = NULL;
   // init_token(data);
}
*/