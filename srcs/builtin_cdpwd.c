/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cdpwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:02:33 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/27 12:23:45 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_status = 1;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
		g_status = 0;
	}
	return (SUCCESS);
}

void	reduce_builtcd(char *oldpwd, char *pwd, char *pwd_ptr)
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
	// if (ft_strncmp(av[0], "cd", 3) == 0 && !av[1])
		
	if (chdir(av[1]) == 0)
		reduce_builtcd(oldpwd, pwd, pwd_ptr);
	else
	{
		perror("chdir");
		g_status = 1;
	}
	free_split(av);
	g_status = 0;
	return (SUCCESS);
}
