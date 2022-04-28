/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:08:36 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/28 12:21:39 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_av(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

char	**create_arg(t_token *list)
{
	t_token	*t;
	char	**av;
	int		count;
	int		i;

	t = list;
	count = 0;
	while (t)
	{
		if (t->type == 7 || t->type == 9 || t->type == 5 || t->type == 6)
			count++;
		t = t->next;
	}
	i = 0;
	av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (NULL);
	t = list;
	while (t && (t->type == 7 || t->type == 9 || t->type == 5 || t->type == 6))
	{
		av[i++] = ft_strdup(t->value);
		t = t->next;
	}
	av[i] = NULL;
	return (av);
}

void	print_env(t_env *our_env)
{
	int	i;
	int	j;

	i = 0;
	while (our_env->envp[i])
	{
		j = 0;
		while (our_env->envp[i][j])
		{
			ft_putchar_fd(our_env->envp[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**create_ourenv(char **tab)
{
	int			i;
	char		**new;
	int			tablen;

	if (!tab)
		return (NULL);
	tablen = 0;
	while (tab[tablen])
		tablen++;
	i = 0;
	new = malloc(sizeof(char *) * (tablen + 1));
	if (new == NULL)
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
