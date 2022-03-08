/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:26:13 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/08 16:22:32 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int parse(char *buf, t_data *data)
{
    int i;

    i = 0;
    data->token = ft_split(buf, ' ');
    while (data->token[i])
    {
        global_check(data->token[i]);
        i++;
    }
 /*  while (data->token[i])
    {
       printf("%s\n", data->token[i]);
       i++;
    }*/
    return (0);
}

