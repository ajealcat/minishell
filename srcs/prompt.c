/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/13 12:10:11 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_test(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->type == word)
			printf("word: |%s|\n", tmp->value);
		else if (tmp->type == t_pipe)
			printf("PIPE: |%s|\n", tmp->value);
		else if (tmp->type == l_red)
			printf("LESS: |%s|\n", tmp->value);
		else if (tmp->type == r_red)
			printf("GREAT: |%s|\n", tmp->value);
		else if (tmp->type == dl_red)
			printf("DLESS: |%s|\n", tmp->value);
		else if (tmp->type == dr_red)
			printf("DGREAT: |%s|\n", tmp->value);
		else if (tmp->type == d_quote)
			printf("DQUOTE: |%s|\n", tmp->value);
		else if (tmp->type == s_quote)
			printf("SQUOTE: |%s|\n", tmp->value);
		else if (tmp->type == var)
			printf("var: |%s|\n", tmp->value);
		tmp = tmp->next;
	}
}

int	print_prompt(t_data *data, char **envp)
{
	char	*cmd;
	t_token	*list;

	(void)envp;
	cmd = "exit";
	while (1)
	{
		list = NULL;
		init_data(data, envp);
		signal(SIGINT, gestion_signaux);
		signal(SIGQUIT, gestion_signaux);
		data->buf = readline(PROMPT);
		if (!data->buf)
		{
			ft_putstr_fd("exit\n", 1);
			free(data);
			exit(0);
		}
		if (data->buf != NULL && ft_strlen(data->buf) != 0)
			add_history(data->buf);
		list = parse(list, data);
	//	print_test(list);
		if (checker_red(list) != FAILURE
			&& unclose_quote(data->str_trimed) != FAILURE)
			parsing_for_exec(list, envp, data);
		if (data != NULL)
		{
			free(data->buf);
			free(data->str_trimed);
		}
		free_list(&list);
	}
	return (SUCCESS);
}
