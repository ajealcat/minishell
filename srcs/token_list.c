/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:53:53 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/11 18:44:07 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(dblist **list) //double ** car la fontction doit directement effectuer
{								//des modifications sur les objets de la liste
	t_token	*tmp;
	t_token	*del;
	
	if (*list != NULL)
	{
		tmp = (*list)->head;
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

int add_list(t_token *token)
{
    if (token == NULL)
    {
        token->prev = NULL;
		token = token;
    }
    else
    {
		list->tail->next = node; //on relie le dernier element de la liste vers le nouvel element
		node->prev = list->tail; //on fait pointer prev vers le dernier element de la liste
		list->tail = node; //on fait pointer la fin de la liste vers le nouvel element
    }
    return (SUCCESS);
}

t_token create_node(t_token *token, char *str, int category)
{
    token = malloc(sizeof(t_token));
    if (!token)
        return (0);
    token->type = category;
    token->value = str;
    token->next = NULL;
    add_list(token);
    return (token);
}
