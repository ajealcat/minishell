/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/25 15:17:03 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*reduce_fonction(char *str, char *tmp, int i, t_token *list)
{
	char	*env;

	tmp = ft_substr(str, (i + 1), (ft_strlen_dollar(str + i) - 1));
	env = gojo_expand(tmp);
	list = create_node(list, env, var);
	return (list);
}

t_token	*reparse_dquote(t_token *list, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
		{
			i++;
			if (str[i] == '$' || str[i] == '\0')
			{
				tmp = ft_substr(str, j, i - j);
				list = create_node(list, tmp, word);
			}
		}
		if (str[i] && str[i] == '$')
		{
			list = reduce_fonction(str, tmp, i, list);
			i += ft_strlen_dollar(str + i);
			j = i;
		}
	}
	return (list);
}


t_token	*token_between_dquote(t_token *list, t_data *data)
{
	int			size;
	int			j;
	char		*tmp;
	int			count;

	count = count_quote(data->str_trimed + data->i, '\"');
	size = ft_strlen_between_quotes(data->str_trimed + data->i, count, '\"');
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
	list = reparse_dquote(list, tmp);
	return (list);
}

int	count_quote(char *str, char quote)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == quote)
			counter++;
		i++;
	}
	return (counter);
}

t_token	*token_between_squote(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;
	int		count;

	count = count_quote(data->str_trimed + data->i, '\'');
	size = ft_strlen_between_quotes(data->str_trimed + data->i, count, '\'');
	tmp = malloc(sizeof(char) * ((size - count) + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	if (ft_strlen(data->str_trimed) == (size_t)count)
		return(NULL);
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
		list = create_node(list, tmp, word);
	}
	return (list);
}