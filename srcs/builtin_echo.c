/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:36:04 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/28 15:32:17 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	printf_echo(char **av, int n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (*av[i] && av[i + 1] && *av[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	g_status = 0;
	return (SUCCESS);
}

int	check_flagn(char *av)
{
	int		j;

	if (ft_strncmp(av, "-n", 2) == 0)
	{
		j = 1;
		while (av[j] == 'n')
			j++;
		if (av[j] == '\0')
			return (SUCCESS);
		else
			return (FAILURE);
	}
	return (FAILURE);
}

int	builtin_echo(t_token *list)
{
	char	**av;
	int		i;

	i = 1;
	av = create_arg(list);
	if (av[1] == NULL)
		write(1, "\n", 1);
	else if (check_flagn(av[i]) == SUCCESS)
	{
		while (check_flagn(av[i]) == SUCCESS)
			i++;
		printf_echo(av + i, 1);
	}
	else
		printf_echo(av + i, 0);
	free_split(av);
	return (SUCCESS);
}
