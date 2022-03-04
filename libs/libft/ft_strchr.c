/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:11:10 by ajearuth          #+#    #+#             */
/*   Updated: 2021/05/26 14:20:31 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	tmp_c;

	tmp_c = (unsigned char) c;
	if (tmp_c == '\0')
	{
		while (*str != '\0')
			++str;
		return ((char *)str);
	}
	while (*str)
	{
		if (*str == tmp_c)
			return ((char *)str);
		else if (*str != tmp_c)
			++str;
	}
	return (NULL);
}
