/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cdpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:02:33 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/14 15:28:59 by fboumell         ###   ########.fr       */
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

int	builtin_cd(t_token *list)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;
	char	**av;

	oldpwd = NULL;
	pwd = NULL;
	pwd_ptr = NULL;
	av = create_arg(list);
	if (chdir(av[1]) == 0)
	{
		pwd = getenv("PWD");
		oldpwd = getenv("OLDPWD");
		if (oldpwd != NULL && pwd != NULL)
			ft_strlcpy(oldpwd, pwd, ft_strlen(oldpwd));
		if (pwd != NULL)
		{
			pwd_ptr = getcwd(NULL, 0);
			ft_strlcpy(pwd, pwd_ptr, ft_strlen(pwd));
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	}
	else
	{
		perror("chdir");
		global_status = 1;
	}
	free_split(av);
	return (SUCCESS);
}
