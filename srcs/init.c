/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:03:52 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/09 14:38:57 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_token(t_token *token)
{
    token->str_trimed = NULL;
    token->i = 0;
}

void init_data(t_data *data)
{
    data->buf = NULL;
}