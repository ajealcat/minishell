/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:14:51 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/15 15:25:31 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strlen_space(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i] != ' ' && ft_isalnum(str[i]) == 1)
        ++i;
    printf("i dans stlren space : %d\n", i);
    return(i);
}