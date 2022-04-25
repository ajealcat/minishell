/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:48:27 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 17:31:33 by ajearuth         ###   ########.fr       */
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

int	free_exit(t_token *list, t_data *data, int code, t_pipex *multi)
{
	if (data != NULL)
	{
		if (data->our_env)
			free_our_env(data->our_env);
		if (data->buf)
			free(data->buf);
		if (data->str_trimed)
			free(data->str_trimed);
		free(data);
	}
	if (list)
		free_list(&list);
	if (multi)
		free_multi(multi);
	rl_clear_history();
	g_status = 0;
	exit(code);
}

int	builtin_exit(t_token *list, t_data *data, t_pipex *multi)
{
	data->our_env->av = create_arg(list);
	if (count_av(data->our_env->av) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		free_exit(list, data, SUCCESS, multi);
	}
	else if (count_av(data->our_env->av) == 2)
	{
		ft_putstr_fd("exit\n", 1);
		if (only_digit(data->our_env->av[1]) == 1)
			free_exit(list, data, ft_atoi(data->our_env->av[1]), multi);
		else
		{
			printf("exit: %s : numeric arg required\n", data->our_env->av[1]);
			free_exit(list, data, ft_atoi(data->our_env->av[1]), multi);
			g_status = 2;
		}
	}
	else
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_status = 1;
	}
	g_status = 0;
	return (SUCCESS);
}
