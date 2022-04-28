/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 12:08:08 by ajearuth         ###   ########.fr       */
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
			list = reduce_reparse_dquote2(i, j, str, list);
		}
		if (str[i] && str[i] == '$')
		{
			tmp = ft_substr(str, (i + 1), (ft_strlen_dollar(str + i) - 1));
			list = reduce_reparse_dquote(tmp, data, list);
			i += ft_strlen_dollar(str + i);
			j = i;
			free(tmp);
		}
	}
	return (list);
}

t_token	*token_between_dquote(t_token *list, t_data *data)
{
	int			size;
	char		*tmp;
	int			count;

	tmp = NULL;
	if (ft_strncmp(data->str_trimed + data->i, "\"\"", 3) == 0)
	{
		list = create_node(list, ft_strdup(""), WORD);
		data->i++;
	}
	else
	{
		count = count_quote(data->str_trimed + data->i, '\"');
		size = ft_strlen_between_quotes(data->str_trimed + data->i, \
			count, '\"');
		tmp = reduce_token_btw_dquote(data, size, count, tmp);
		list = reparse_dquote(list, tmp, data);
	}
	free(tmp);
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
	char	*tmp;
	int		count;

	tmp = NULL;
	if (ft_strncmp(data->str_trimed + data->i, "''", 3) == 0)
		list = create_node(list, ft_strdup(""), WORD);
	else
	{
		count = count_quote(data->str_trimed + data->i, '\'');
		size = ft_strlen_between_quotes(data->str_trimed + data->i, \
			count, '\'');
		tmp = reduce_token_btw_squote(data, size, count, tmp);
		list = create_node(list, tmp, S_QUOTE);
	}
	return (list);
}
