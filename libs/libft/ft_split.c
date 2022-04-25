/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:57:56 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 17:17:01 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizeofWORD(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

static int	ft_count_WORDs(const char *str, char c)
{
	int	WORDs;
	int	state;

	WORDs = 0;
	state = 1;
	while (*str)
	{
		if (*str == c)
			state = 1;
		else if (state == 1)
		{
			WORDs++;
			state = 0;
		}
		++str;
	}
	return (WORDs);
}

static char	**ft_error(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		--i;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		index;
	int		i;

	if (str == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_WORDs(str, c) + 1));
	if (tab == NULL)
		return (NULL);
	index = 0;
	while (ft_count_WORDs(str, c))
	{
		while (*str && *str == c)
			++str;
		tab[index] = malloc(sizeof(char) * ft_sizeofWORD(str, c) + 1);
		if (tab[index] == 0)
			return (ft_error(tab, index));
		i = 0;
		while (*str && *str != c)
			tab[index][i++] = *str++;
		tab[index][i] = '\0';
		index++;
	}
	tab[index] = 0;
	return (tab);
}
