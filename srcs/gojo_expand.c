/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gojo_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:32:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/18 16:00:12 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*gojo_expand(char *tmp)
{
	char	*env;

	env = getenv(tmp);
	if (env == NULL)
		return (NULL);
	return (env);
}
