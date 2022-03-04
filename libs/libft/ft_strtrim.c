/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:04:56 by ajearuth          #+#    #+#             */
/*   Updated: 2021/05/28 14:54:32 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ret;
	size_t	start;
	size_t	i;
	size_t	end;

	start = 0;
	i = 0;
	if (!set || !s1)
		return (NULL);
	end = ft_strlen(s1);
	while (ft_is_charset(s1[start], set))
		++start;
	while (end > start && ft_is_charset(s1[end - 1], set))
		--end;
	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	if (ret == NULL)
		return (NULL);
	while (start < end)
	{
		ret[i] = s1[start];
		++start;
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
