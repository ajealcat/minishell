/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:37:12 by ajearuth          #+#    #+#             */
/*   Updated: 2021/12/29 17:13:04 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_strlen_putnbrbase(const char *base)
{
	long	i;

	i = 0;
	while (base[i])
		++i;
	return (i);
}

static int	ft_checkbase(const char *base)
{
	int	i;
	int	j;

	i = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
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

void	ft_putnbr_base(int nbr, const char *base, int fd)
{
	long	nb;

	nb = nbr;
	if (ft_checkbase(base) == 1)
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb = nb * (-1);
		}
		if (nb < ft_strlen_putnbrbase(base) && nb >= 0)
		{
			ft_putchar_fd(base[nb], fd);
		}
		else
		{
			ft_putnbr_base(nb / ft_strlen_putnbrbase(base), base, fd);
			ft_putnbr_base(nb % ft_strlen_putnbrbase(base), base, fd);
		}
	}
}
