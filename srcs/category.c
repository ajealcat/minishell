/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:57:17 by Fahima42          #+#    #+#             */
/*   Updated: 2022/03/14 17:40:35 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *r_redirect(t_token *list, t_data *data)
{
    if (data->str_trimed[data->i + 1] == '>')
        list = create_node(list, ">>", dr_red);
	else
		list = create_node(list, ">", r_red);
	return (list);
}

t_token *l_redirect(t_token *list, t_data *data)
{
    if (data->str_trimed[data->i + 1] == '<')
        list = create_node(list, "<<", dl_red);
	else
		list = create_node(list, "<", l_red);
	return (list);
}

t_token *token_word(t_token *list, t_data *data)
{
	int		size;
	int		j;
	char	*tmp;

    size = ft_strlen_space(data->str_trimed);
	printf("size in token word : %d\n", size);
    tmp = malloc(sizeof(char) * (size + 1));
	j = 0;
	while (ft_isalnum(data->str_trimed[data->i]) == 1 && j <= size)
	{
		tmp[j] = data->str_trimed[data->i];
		data->i++;
		j++;
	}
	tmp[j] = '\0';
	printf("i et c : %d\n%c\n", data->i, data->str_trimed[data->i]);
	list = create_node(list, tmp, word);
	printf("return list dans token_word : %s\n", list->value);
	printf("list token_word: %d\n", list->type);
	return (list);
}