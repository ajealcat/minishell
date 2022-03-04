/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:49:13 by ajearuth          #+#    #+#             */
/*   Updated: 2021/05/26 14:54:23 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t			size;

	size = ft_strlen(str);
	if (!str)
		return (NULL);
	while (size + 1)
	{
		if (str[size] == (char)c)
			return ((char *)(str + size));
		--size;
	}
	return (NULL);
}
