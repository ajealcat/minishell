/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:53:53 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/10 14:57:01 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int create_node(char *str, int category, t_token *token)
{
    t_token *new_node;

    new_node = malloc(sizeof(t_token));
    if (!new_node)
        return (0);
    new_node->type = category;
    new_node->data_token = str;
    new_node->next = NULL;
    add_list(new_node, list);
    return (SUCCESS);
    
}