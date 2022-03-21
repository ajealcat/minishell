/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/21 15:08:30 by ajearuth         ###   ########.fr       */
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

	size = ft_strlen_between_quotes(data->str_trimed + data->i);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	j = 0;
	while (data->str_trimed[data->i] && j < size)
	{
		printf("data->i pdt le calcul des quotes = %d\n", data->i);
		tmp[j] = data->str_trimed[data->i + 1];
		data->i++;
		j++;
	}
	tmp[j - 1] = '\0';
	printf("data->i dans le calcul des quotes = %d\n", data->i);
	list = create_node(list, tmp, word);
	return (list);
}
