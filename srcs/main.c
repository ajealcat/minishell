/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:14 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/15 12:44:42 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gerer le "$?" --> doit afficher le dernier code d'erreur
// revoir les dquote et squote vides ou avec juste un espace
// heredoc + signaux + redirections
// $ + var en minuscule segfault

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	t_env	*our_env;	

	(void)ac;
	(void)av;
	// g_status = 0;
	our_env = malloc(sizeof(t_env));
	if (!our_env)
		return (FAILURE);
	our_env->envp = create_ourenv(envp);
	our_env->av = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (FAILURE);
	if (ac || av)
		print_prompt(data, our_env);
	free_our_env(our_env);
	return (SUCCESS);
}
