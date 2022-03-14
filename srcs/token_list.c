/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:53:53 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/14 16:41:37 by Fahima42         ###   ########.fr       */
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

t_token *add_list(t_token *list, t_token *new_token)
{
	t_token *tmp;
	
    if (list == NULL)
    {
        new_token->prev = NULL;
		list = new_token;
    }
    else
    {
		tmp = list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
    }
    return (list);
}

t_token *create_node(t_token *list, char *str, int category)
{
   t_token *new_token;
   
	new_token = malloc(sizeof(t_token));
    if (!new_token)
	{
		perror("Malloc Failure");
        return (0);
	}
    new_token->type = category;
    new_token->value = str;
    new_token->next = NULL;
    list = add_list(list, new_token);
    return (list);
}
