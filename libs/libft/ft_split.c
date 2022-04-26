/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:57:56 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/26 16:06:57 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sizeofwords(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

static int	ft_count_words(const char *str, char c)
{
	int	words;
	int	state;

	words = 0;
	state = 1;
	while (*str)
	{
		if (*str == c)
			state = 1;
		else if (state == 1)
		{
			words++;
			state = 0;
		}
		++str;
	}
	return (words);
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
	tab = malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (tab == NULL)
		return (NULL);
	index = 0;
	while (ft_count_words(str, c))
	{
		while (*str && *str == c)
			++str;
		tab[index] = malloc(sizeof(char) * ft_sizeofwords(str, c) + 1);
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
