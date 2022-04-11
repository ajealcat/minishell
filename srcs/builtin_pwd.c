/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:02:33 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/11 12:09:00 by fboumell         ###   ########.fr       */
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

char	*move_pwd(char **av, char *pwd)
{
	char	*new_path;
//	char	*pwd;

	new_path = NULL;
	if (av[1])
	{
//		pwd = getenv("PWD");
		new_path = ft_strjoin(pwd, "/");
		new_path = ft_strjoin(new_path, av[1]);
		printf("new_path = %s\n", new_path);
		if (open(new_path, O_DIRECTORY) == -1)
			perror("cd");
		return (new_path);
	}
	return (new_path);
}


int	builtin_cd(t_token *list)
{
	char	*new_path;
	char	**av;
	char	*pwd;

	new_path = NULL;
	av = create_arg(list);
	pwd = getenv("PWD");
	if (count_av(av) > 2)
		perror("cd");
	else
	{
		new_path = move_pwd(av, pwd);
		if (chdir(new_path) == FAILURE)
			perror("chdir()");
	}
	return (SUCCESS);
}
