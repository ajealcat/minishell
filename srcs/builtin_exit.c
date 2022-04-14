/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:48:27 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/14 15:28:44 by fboumell         ###   ########.fr       */
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

int	free_exit(t_token *list, t_data *data, int code, t_env *our_env)
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
	if (our_env)
		free_our_env(our_env);
	rl_clear_history();
	global_status = 0;
	exit(code);
}

int	builtin_exit(t_token *list, t_data *data, t_env *our_env)
{
	our_env->av = create_arg(list);
	if (count_av(our_env->av) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		free_exit(list, data, SUCCESS, our_env);
	}
	else if (count_av(our_env->av) == 2)
	{
		ft_putstr_fd("exit\n", 1);
		if (only_digit(our_env->av[1]) == 1)
			free_exit(list, data, ft_atoi(our_env->av[1]), our_env);
		else
		{
			printf("exit: %s : numeric argument required\n", our_env->av[1]);
			free_exit(list, data, ft_atoi(our_env->av[1]), our_env);
			global_status = 2;
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("exit : too many arguments\n", 2);
		global_status = 1;
	}
	return (SUCCESS);
}
