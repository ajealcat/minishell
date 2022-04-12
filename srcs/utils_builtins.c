/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:08:36 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/12 13:55:32 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
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

void	print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			ft_putchar_fd(env[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}
