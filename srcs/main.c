/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:14 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/26 15:50:46 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// heredoc + signaux + redirections
// $ + var en minuscule segfault
// cd sans arguments doit nous ramener au home

int	g_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		return (FAILURE);
	data->our_env = malloc(sizeof(t_env));
	if (!data->our_env)
		return (FAILURE);
	data->our_env->envp = create_ourenv(envp);
	data->our_env->av = NULL;
	if (ac || av)
		print_prompt(data);
	if (data->our_env)
		free_our_env(data->our_env);
	return (SUCCESS);
}
