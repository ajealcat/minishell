/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/26 13:43:28 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_test(t_token *list)
// {
// 	t_token	*tmp;

// 	tmp = list;
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == WORD)
// 			printf("WORD: |%s|\n", tmp->value);
// 		else if (tmp->type == T_PIPE)
// 			printf("PIPE: |%s|\n", tmp->value);
// 		else if (tmp->type == L_RED)
// 			printf("LESS: |%s|\n", tmp->value);
// 		else if (tmp->type == R_RED)
// 			printf("GREAT: |%s|\n", tmp->value);
// 		else if (tmp->type == DL_RED)
// 			printf("DLESS: |%s|\n", tmp->value);
// 		else if (tmp->type == DR_RED)
// 			printf("DGREAT: |%s|\n", tmp->value);
// 		else if (tmp->type == D_QUOTE)
// 			printf("DQUOTE: |%s|\n", tmp->value);
// 		else if (tmp->type == S_QUOTE)
// 			printf("SQUOTE: |%s|\n", tmp->value);
// 		else if (tmp->type == VAR_WORD)
// 			printf("VAR_WORD: |%s|\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// }

void	free_data_buf(t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	free_our_env(data->our_env);
	free(data);
	exit(0);
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		free(data->buf);
		free(data->str_trimed);
	}
}

int	print_prompt(t_data *data)
{
	char	*cmd;
	t_token	*list;

	cmd = "exit";
	while (1)
	{
		list = NULL;
		init_data(data);
		signal(SIGINT, gestion_signaux);
		signal(SIGQUIT, gestion_signaux);
		data->buf = readline(PROMPT);
		if (!data->buf)
			free_data_buf(data);
		if (data->buf != NULL && ft_strlen(data->buf) != 0)
			add_history(data->buf);
		list = parse(list, data);
		// print_test(list);
		if (checker_red(list) != FAILURE
			&& unclose_quote(data->str_trimed) != FAILURE)
			parsing_for_exec(list, data);
		free_data(data);
		free_list(&list);
	}
	return (SUCCESS);
}
