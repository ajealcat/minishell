/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:00:34 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/16 17:33:14 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	free_list(t_token **list) //double ** car la fontction doit directement effectuer
{								//des modifications sur les objets de la liste
	t_token	*tmp;
	t_token	*del;
	if (*list != NULL)
	{
		tmp = (*list);
		while (tmp != NULL)
		{
			del = tmp;
			tmp = tmp->next;
			free(del);
		}
		(*list) = NULL;
	}
}

int message_error(t_token *list, t_data *data)
{
    // ft_putstr_fd(str, 2);
    if (list != NULL)
	{	
		// printf("tu beug ici?\n");
        free_list(&list);
	}
    if (data)
    {
		// printf("tu beug dans data? dis le nous stp\n");
        if (data->str_trimed)
    		free(data->str_trimed);
        if (data->buf)
    		free(data->buf);
    }
    return (FAILURE);
}