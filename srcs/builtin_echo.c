/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:36:04 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/08 13:13:29 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	printf_echo(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("%s", av[i + 1]);
	}
	return (SUCCESS);
}

char	**create_arg(t_token *list)
{
	t_token	*tmp;
	char	**av;
	int		count;
	int		i;

	tmp = list;
	while (tmp)
	{
		while (tmp->type == word)
			count++;
	}
	i = 0;
	av = malloc(sizeof(char *) * count + 1);
	if (!av)
		return (NULL);
	tmp = list;
	while (tmp && tmp->type == word)
	{
		av[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
	av[i] = "\0";
	return (av);
}

int	check_flagn(char **av)
{
	int		j;

	if (ft_strncmp(av[1], "-n", 2) == 0)
	{
		j = 0;
		while (av[1][j] == 'n')
			j++;
		if (av[1][j] == "\0")
			return (SUCCESS);
		else
			return (FAILURE);
	}
	return (FAILURE);
}

int	builtin_echo(t_token *list)
{
	int		i;
	char	**av;
	t_token	*tmp;

	tmp = list;
	while (tmp && tmp->type == word || tmp->type == var)
	{
		if (tmp->type == var)
			tmp->type = word;
		tmp = tmp->next;
	}
	
	av = create_arg(list);

}

