/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:03:52 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/17 14:50:46 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_token(t_token *list)
{
    list->type = 0;
    list->value = NULL;
    list->next = NULL;
    list->prev = NULL;
}

void  init_data(t_data *data)
{
    data->buf = NULL;
    data->str_trimed = NULL;
    data->i = 0;
}
