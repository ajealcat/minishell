/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gojo_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:32:36 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/13 15:16:43 by ajearuth         ###   ########.fr       */
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
