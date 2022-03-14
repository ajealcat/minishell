/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:00:34 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/14 18:07:32 by Fahima42         ###   ########.fr       */
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
		free(*list);
		(*list) = NULL;
	}
}

int message_error(char *str, t_token *list, t_data *data)
{
    ft_putstr_fd(2, str);
    if (list != NULL)
    {
        free_list(list);
    }
    if (data != NULL)
    {
        free(data->str_trimed);
        free(data->buf);
    }
    return (FAILURE);
}