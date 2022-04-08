/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:36:04 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/08 16:10:57 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	printf_echo(char **av, int n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		printf("%s", av[i]);
		if (*av[i] && av[i + 1] && *av[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (SUCCESS);
}

char	**create_arg(t_token *list)
{
	t_token	*tmp;
	char	**av;
	int		count;
	int		i;

	tmp = list;
	count = 0;
	while (tmp)
	{
		if (tmp->type == word || tmp->type == var_word)
			count++;
		tmp = tmp->next;
	}
	i = 0;
	av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (NULL);
	tmp = list;
	while (tmp && (tmp->type == word || tmp->type == var_word))
	{
		av[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
	av[i] = NULL;
	free(tmp);
	return (av);
}

int	check_flagn(char *av)
{
	int		j;

	if (ft_strncmp(av, "-n", 2) == 0)
	{
		j = 1;
		while (av[j] == 'n')
			j++;
		if (av[j] == '\0')
			return (SUCCESS);
		else
			return (FAILURE);
	}
	return (FAILURE);
}

int	builtin_echo(t_token *list)
{
	char	**av;
	int		i;

	i = 1;
	av = create_arg(list);
	if (av[1] == NULL)
		write(1, "\n", 1);
	else if (check_flagn(av[i]) == SUCCESS)
	{
		while (check_flagn(av[i]) == SUCCESS)
			i++;
		printf_echo(av + i, 1);
	}
	else
		printf_echo(av + i, 0);
	free_split(av);
	return (SUCCESS);
}

