/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:17:40 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/11 17:27:23 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int print_prompt(t_token *token)
{
//	t_token *token;
	char *cmd = "exit";
	
//	token = NULL;
	printf("token buffer null |%s|\n", token->buf);
	//init_token(token);
	while (1)
	{
		token->buf = readline(PROMPT);
		printf("token buffer after readline : |%s|\n", token->buf);
		fflush(stdout);
		if (token->buf != NULL)
			add_history(token->buf);
		parse(token);
		if (ft_strncmp(token->buf, cmd, 5) == 0)
			exit(0);
		free(token->buf);
	}
	return (0);
}