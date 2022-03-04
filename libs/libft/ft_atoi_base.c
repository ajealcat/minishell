/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:51:18 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/29 17:11:32 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printbase(const char *base, char c)
{
	int	i;

	i = 0;
	while (base[i] != c)
		i++;
	return (i);
}

static int	ft_isbase(const char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_checkbase(const char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if ((base[i] > 8 && base[i] < 14) || base[i] == 32)
			return (0);
		j = 0;
		while (base[j])
		{
			if (base[i] == base[j] && j != i)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi_base(char *str, const char *base)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (ft_checkbase(base) == 1)
	{
		while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
		while (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign = -sign;
			i++;
		}
		while (str[i] && ft_isbase(base, str[i]))
		{
			nb = nb * ft_strlen(base) + ft_printbase(base, str[i]);
			i++;
		}
	}
	return (nb * sign);
}
