/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/25 17:17:18 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*reparse_dquote(t_token *list, char *str, t_data *data)
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
				list = create_node(list, tmp, WORD);
			}
		}
		if (str[i] && str[i] == '$')
		{
			tmp = ft_substr(str, (i + 1), (ft_strlen_dollar(str + i) - 1));
			tmp = gojo_expand(tmp, data->our_env);
			list = create_node(list, tmp, VAR_WORD);
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

	if (ft_strncmp(data->str_trimed + data->i, "\"\"", 3) == 0)
	{
		list = create_node(list, " ", VAR_WORD);
		data->i++;
	}
	else
	{
		count = count_quote(data->str_trimed + data->i, '\"');
		size = ft_strlen_between_quotes(data->str_trimed + data->i, \
			count, '\"');
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
		list = reparse_dquote(list, tmp, data);
	}
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

	if (ft_strncmp(data->str_trimed + data->i, "''", 3) == 0)
		list = create_node(list, " ", VAR_WORD);
	else
	{
		count = count_quote(data->str_trimed + data->i, '\'');
		size = ft_strlen_between_quotes(data->str_trimed + data->i, \
			count, '\'');
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
			list = create_node(list, tmp, WORD);
		}
	}
	return (list);
}
