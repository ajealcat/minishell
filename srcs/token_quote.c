/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/22 17:44:20 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*reparse_dquote(t_token *list, char *str)
{
	int		i;
	int j;
	char	*tmp;

	i = 0;
	printf("str : [%s]\n", str);
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen_encore(str) + 1));
	while (str[i]) && str[i] != '$')
	{
		printf("str[i] : [%c]\n", str[i]);
		printf("tmp[j] : [%c]\n", tmp[j]);
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	list = create_node(list, tmp, word);
	if (str[i] == '$')
	{
		tmp = ft_substr(str, i, ft_strlen_dollar(str + i));
		list = create_node(list, tmp, var);
		i++;
	}
	return (list);
}

t_token	*token_between_dquote(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;
	int		count;

	count = count_quote(data->str_trimed + data->i, '\"');
	//printf("count : %d\n", count);
	size = ft_strlen_between_quotes(data->str_trimed + data->i, count, '\"');
	tmp = malloc(sizeof(char) * ((size - count) + 1));
//	printf("size : %d\n", size);
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && count != 0)
	{
		if (data->str_trimed[data->i] == '\"')
		{
			count--;
			data->i++;
		}
		else
			tmp[j++] = data->str_trimed[data->i++];
		//printf("j : %d\n", j);
	}
	tmp[j] = '\0';
	list = reparse_dquote(list, tmp);
//	list = create_node(list, tmp, d_quote);
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
