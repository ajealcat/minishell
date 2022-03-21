/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/21 18:01:26 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  Pour verifier si le space doit devenir un mot car il est entre guillemets 
	ou si on peut juste le sauter parce qu'osef */
/*
int	is_quote_odd(t_token *list, t_data *data)
{
	t_token	*tmp;
	int i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == d_quote)
			i++;
		tmp = tmp->prev;
	}
	if (i % 2 == 0)
		return (FAILURE);
	return (SUCCESS);
}*/

t_token	*token_between_dquote(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;
	int		count;

	count = count_quote(data->str_trimed + data->i, '\"');
	size = ft_strlen_between_quotes(data->str_trimed + data->i, '\"', count);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && j < size)
	{
		tmp[j] = data->str_trimed[data->i + 1];
		data->i++;
		j++;
	}
	tmp[j - 1] = '\0';
	list = create_node(list, tmp, d_quote);
	data->i--;
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
		{
			if (str[i - 1] == '\\')
				i++;
			else
				counter++;
		}
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
	size = ft_strlen_between_quotes(data->str_trimed + data->i, '\'', count);
	printf("size : %d\n", size);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && j < size)
	{
		if (data->str_trimed[data->i] == '\'')
		{
			if (data->str_trimed[data->i] == '\\'
				&& data->str_trimed[data->i + 1] == '\'')
				data->i++;
			data->i++;
		}
		printf(" le char : %c\n", data->str_trimed[data->i]);
		tmp[j] = data->str_trimed[data->i];
		data->i++;
		j++;
	}
	tmp[j] = '\0';
	list = create_node(list, tmp, s_quote);
	data->i--;
	return (list);
}
