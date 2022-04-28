/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:54:57 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 21:55:37 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s2)
		return ((unsigned char)(*s1));
	else if (!s1)
		return ((unsigned char)(*s2));
	while ((*s1 || *s2) && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
