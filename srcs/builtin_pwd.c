/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:02:33 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/08 12:22:09 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}

int	builtin_cd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (chdir("..") == FAILURE)
		perror("chdir()");
	free(pwd);
	return (SUCCESS);
}
