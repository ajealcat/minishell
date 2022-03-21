/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:40:58 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/21 12:22:31 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  Pour verifier si le space doit devenir un mot car il est entre guillemets 
	ou si on peut juste le sauter parce qu'osef */



t_token	*token_between_dquote(t_token *list, t_data *data)
{
	int j;
	t_token	*tmp_list;
	char *tmp_str;

	j = 0;
	tmp_list = list;
	tmp_str = malloc ... 

	if (is_quote_pair(tmp) == SUCCESS)
	{
		data->i++;
		return ();
	}
	while (is_quote_pair(tmp_list) == FAILURE)
	{
		tmp[j] = data->str_trimed[data->i];
		j++;
	}
}