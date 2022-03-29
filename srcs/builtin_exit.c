/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:48:27 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/29 15:53:23 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_exit(t_token *list, char **av)
{
	if ()
	if (list != NULL)
		free_list(list);
	if (our_path != NULL)
		free_our_path(our_path);
	exit (0);
}
