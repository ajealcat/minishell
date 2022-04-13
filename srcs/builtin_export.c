/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:28:13 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/13 14:00:29 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var(char **our_env, char *tmp)
{
	int	i;

	i = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], tmp, ft_strlen(tmp)) == 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	replace_value(char **our_env, char **tmp)
{
	int	i;

	i = 0;
	while (our_env[i])
	{
		if (ft_strncmp(our_env[i], tmp[0], ft_strlen(tmp[0])) == 0)
			norm_export(tmp, our_env, i);
		i++;
	}
}

void	norm_export(char **tmp, char **our_env, int i)
{
	// int	j;
	// int	k;

	// j = 0;
	// while (our_env[i][j] != '=')
	// 	j++;
	// k = 0;
	// if (our_env[i][j] == '=')
	// {
	// 	j++;
	// 	while (our_env[i][j])
	// 	{
	// 		while (tmp[1][k])
	// 		{
	// 			our_env[i][j] = tmp[1][k];
	// 			k++;
	// 			j++;
	// 		}
	// 		our_env[i][j] = '\0';
	// 		j++;
	// 	}
	// }
	char    *tmp2;

	if (tmp == NULL || our_env == NULL)
		return ;
	tmp2 = ft_strjoin(tmp[0], "=");
	// free(our_env[i]);
	if (tmp[1] == NULL)
		our_env[i] = ft_strdup(tmp2);
	else
		our_env[i] = ft_strjoin(tmp2, tmp[1]);
	free(tmp2);

}

char	**create_value(char **our_env, char *av)
{
	// int		i;
	// int		j;
	// char	**tmp_str;

	// i = 0;
	// j = 1;
	// while (our_env[i])
	// 	i++;
	// tmp_str = malloc(sizeof(char *) * (i + (count_av(av) - 1)) + 1);
	// i = 0;
	// while (our_env[i])
	// {
	// 	tmp_str[i] = ft_strdup(our_env[i]);
	// 	i++;
	// }
	// while (av[j])
	// {
	// 	tmp_str[i] = ft_strdup(av[j]);
	// 	j++;
	// 	i++;
	// }
	// tmp_str[i] = NULL;
	// return (tmp_str);
	char	**tmp;
	int		i;

	i = 0;
	if (our_env == NULL || av == NULL)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(our_env) + 2));
	while (our_env[i])
	{
		tmp[i] = ft_strdup(our_env[i]);
		i++;
	}
	tmp[i] = ft_strdup(av);
	tmp[i + 1] = NULL;
	return (tmp);
}

int	builtin_export(t_token *list, char **our_env)
{
	// char	**tmp;
	// char	**av;
	// int		i;

	// i = 1;
	// av = create_arg(list);
	// tmp = NULL;
	// if (count_av(av) > 1)
	// {
	// 	while (av[i])
	// 	{
	// 		tmp = ft_split(av[i], '=');
	// 		if (is_var(our_env, tmp[0]) == SUCCESS)
	// 			replace_value(our_env, tmp);
	// 		else
	// 		{	
	// 			tmp = create_value(our_env, av);
	// 			our_env = tmp;
	// 		}
	// 		i++;
	// 	}
	// }
	// free_split(av);
	// free_split(tmp);
	// return (SUCCESS);
	char	**tmp;
	char	**av;
	int		i;

	i = 1;
	av = create_arg(list);
	tmp = NULL;
	if (count_av(av) > 1)
	{
		while (av[i])
		{
			tmp = ft_split(av[i], '=');
			if (is_var(our_env, tmp[0]) == SUCCESS)
			{
				replace_value(our_env, tmp);
				free_split(tmp);
			}
			else
			{
				free_split(tmp);
				tmp = create_value(our_env, av[i]);
				free_split(our_env);
				our_env = tmp;
			}
			i++;
		}
	}
	free_split(av);
	return (SUCCESS);
}
