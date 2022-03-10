/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:53:53 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/10 16:57:43 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_list(dblist *list)
{
	list->head = NULL;
	list->tail = NULL;
}

void	free_list(dblist **list) //double ** car la fontction doit directement effectuer
{								//des modifications sur les objets de la liste
	t_token *tmp;
	t_token *del;
	
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

int add_list(t_token *node)
{
	dblist *list;
    
    if (list->tail == NULL)
    {
        node->prev = NULL;
		list->head = node;
		list->tail = node;
    }
    else
    {
		list->tail->next = node; //on relie le dernier element de la liste vers le nouvel element
		node->prev = list->tail; //on fait pointer prev vers le dernier element de la liste
		list->tail = node; //on fait pointer la fin de la liste vers le nouvel element
    }
    return (SUCCESS);
}

int create_node(char *str, int category, t_token *token)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return (0);
    new_node->type = category;
    new_node->value = str;
    new_node->next = NULL;
    add_list(new_node);
    return (SUCCESS);
}