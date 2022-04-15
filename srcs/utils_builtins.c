/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:08:36 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/15 12:37:07 by ajearuth         ###   ########.fr       */
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
