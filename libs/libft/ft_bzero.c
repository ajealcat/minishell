/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 12:46:20 by ajearuth          #+#    #+#             */
/*   Updated: 2021/05/23 14:34:32 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		*tmp = '\0';
		++tmp;
		++i;
	}
}
