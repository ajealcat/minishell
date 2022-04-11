/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:14 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/11 15:43:36 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gerer le "$?" --> doit afficher le dernier code d'erreur
// revoir les dquote et squote vides ou avec juste un espace
// heredoc + signaux + redirections

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		return (FAILURE);
	if (data == NULL)
		return (FAILURE);
	if (ac || av)
	{
		print_prompt(data, envp);
	}
	return (SUCCESS);
}
