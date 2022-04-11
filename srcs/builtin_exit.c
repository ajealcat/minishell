/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:48:27 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/11 13:22:44 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	only_digit(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		while (av[i] == '-' || av[i] == '+')
		{
			i++;
			count++;
		}
		while (av[i])
		{
			if (!ft_isdigit(av[i]))
				return (FAILURE);
			i++;
		}
		if (count > 1)
			return (3);
	}
	return (1);
}

int	free_exit(t_token *list, t_data *data, int code, char **av)
{
	if (data != NULL)
	{
		if (data->buf)
			free(data->buf);
		if (data->str_trimed)
			free(data->str_trimed);
		free(data);
	}
	if (list)
		free_list(&list);
	if (av)
		free_split(av);
	rl_clear_history();
	exit(code);
}

int	builtin_exit(t_token *list, t_data *data)
{
	char **av;

	av = create_arg(list);
	if (count_av(av) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		free_exit(list, data, SUCCESS, av);
	}
	else if (count_av(av) == 2)
	{
		ft_putstr_fd("exit\n", 1);
		if (only_digit(av[1]) == 1)
			free_exit(list, data, ft_atoi(av[1]), av);
		else
		{
			printf("exit: %s : numeric argument required\n", av[1]);
			free_exit(list, data, ft_atoi(av[1]), av);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("exit : too many arguments\n", 2);
	}
	return (SUCCESS);
}
