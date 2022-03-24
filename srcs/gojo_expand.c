/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gojo_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:32:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/24 11:33:28 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. parcours la liste pour trouver les var
2. envoyer les var dans getenv pour voir si ils existent
3. malloc la chaine a la taille du resultat de getenv ??
4. remplacer la value du var par le resultat de get env
5. Si getenv return nul on relance un prompt sans rien faire */

char	*gojo_expand(char *tmp)
{
	char	*env;

	env = getenv(tmp);
	if (env == NULL)
		return (NULL);
	return (env);
}
