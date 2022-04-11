/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:36:04 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/11 12:09:18 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	printf_echo(char **av, int n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("%s", av[i]);
		if (*av[i] && av[i + 1] && *av[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
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

