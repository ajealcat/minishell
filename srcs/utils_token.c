/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:08:21 by fboumell          #+#    #+#             */
/*   Updated: 2022/04/26 16:55:37 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*reduce_reparse_dquote(char *tmp, t_data *data, t_token *list)
{
	char	*env;

	env = gojo_expand(tmp, data->our_env);
	if (env)
		list = create_node(list, env, VAR_WORD);
	else
		list = create_node(list, "", VAR_WORD);
	return (list);
}

t_token	*reduce_reparse_dquote2(int i, int j, char *str, t_token *list)
{
	char	*tmp;

	if (str[i] == '$' || str[i] == '\0')
	{
		tmp = ft_substr(str, j, i - j);
		list = create_node(list, tmp, WORD);
	}
	return (list);
}

char	*reduce_token_btw_dquote(t_data *data, int size, int count, char *tmp)
{
	int		j;

	tmp = malloc(sizeof(char) * ((size - count) + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && j < (size - count))
	{
		if (data->str_trimed[data->i] == '\"')
			data->i++;
		else
			tmp[j++] = data->str_trimed[data->i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*reduce_token_btw_squote(t_data *data, int size, int count, char *tmp)
{
	int	j;

	tmp = malloc(sizeof(char) * ((size - count) + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	if (ft_strlen(data->str_trimed) == (size_t)count)
		return (NULL);
	else
	{
		while (data->str_trimed[data->i] && j < (size - count))
		{
			if (data->str_trimed[data->i] == '\'')
				data->i++;
			else
				tmp[j++] = data->str_trimed[data->i++];
		}
		tmp[j] = '\0';
	}
	return (tmp);
}

t_token	*reduce_token_dollar(char *tmp, t_data *data, t_token *list)
{
	char	*env;

	env = gojo_expand(tmp, data->our_env);
	if (env)
	{
		list = create_node(list, env, VAR_WORD);
		free(tmp);
		return (list);
	}
	else
	{
		list = create_node(list, "", VAR_WORD);
		free(tmp);
		return (list);
	}
	return (list);
}
