/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/23 13:01:32 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// printf pour test 

//			printf("i : %d\n", i);
//	printf("str : [%s]\n", str);
//		printf("j = i : %d\n", j);
//			printf("i quand il trouve un $ : %d\n", i);
//			printf("tmp apres $ : [%s]\n", tmp);


// Marche pas  vaiment mais ca segfault pas 

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
			if (str[i] == '$')
			{
				tmp = ft_substr(str, j, i);
				list = create_node(list, tmp, word);
			}
		}
		if (str[i] && str[i] == '$')
		{
			tmp = ft_substr(str, i, ft_strlen_dollar(str + i));
			list = create_node(list, tmp, var);
		}
		while (str[i] != ' ')
		{
			i++;
			j = i;
		}
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
	size = ft_strlen_between_quotes(data->str_trimed + data->i, count, '\"');
	tmp = malloc(sizeof(char) * ((size - count) + 1));
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
