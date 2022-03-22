/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/22 15:18:31 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*spe_quote_dollar(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;

	size = ft_strlen_word(data->str_trimed + data->i + 1);
	printf("size quote dol : %d\n", size);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && j < size)
	{
		if (data->str_trimed[data->i] == '\"')
			data->i++;
		else
			tmp[j++] = data->str_trimed[data->i++];
	}
	tmp[j] = '\0';
	list = create_node(list, tmp, d_quote);
	data->i++;
	return (list);
}

t_token	*token_between_dquote(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;
	int		count;

	if (data->str_trimed[data->i + 1] == '$')
		list = spe_quote_dollar(list, data);
	count = count_quote(data->str_trimed + data->i, '\"');
	printf("count : %d\n", count);
	size = ft_strlen_between_quotes(data->str_trimed + data->i, count, '\"');
	tmp = malloc(sizeof(char) * ((size - count) + 1));
	printf("size : %d\n", size);
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && j < size)
	{
		if (data->str_trimed[data->i] == '\"')
			data->i++;
		else
			tmp[j++] = data->str_trimed[data->i++];
	}
	tmp[j] = '\0';
	list = create_node(list, tmp, d_quote);
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
	while (data->str_trimed[data->i] && j < size)
	{
		if (data->str_trimed[data->i] == '\'')
			data->i++;
		else
			tmp[j++] = data->str_trimed[data->i++];
	}
	tmp[j] = '\0';
	list = create_node(list, tmp, word);
	data->i--;
	return (list);
}
