/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:19:05 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/11 15:54:16 by Fahima42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
//# include "../libs/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	char			*str_trimed;
	char			*value;
	int				i;
	int				type;
	struct s_token *prev;
	struct s_token *next;
//	struct s_list *list;
} t_token;

typedef struct s_list
{
	t_token *head;
	t_token	*tail;
} dblist;

typedef struct s_data
{
	char *buf;
	t_token *token;
} t_data;

	/* prompt.c */
int print_prompt(void);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

	/* init.c */
void init_token(t_token *token);
void	init_list(dblist *list);
void init_data(t_data *data);

	/* parse.c */
int parse(t_data *data);
char	*ft_strtrim(const char *s1, const char *set);
int	check_category(t_token *token);

	/* protection_quote.c */
int check_quotes(char *token);

	/* check_parse.c */
int	unclose_quote(char *str);
int	checker_red(t_token *token);

	/* utils.c */
int ft_strlen_space(char *str);
int	ft_isalpha(int c);

	/* category */ 
void r_redirect(t_token *token);
void l_redirect(t_token *token);
int	token_word(t_token *token);

	/* token_list.c */
void	init_list(dblist *list);
void	free_list(dblist **list);
int add_list(t_token *node);
int create_node(char *str, int category);

	/* is_it_available.c */
int	is_valid_left(t_token *token);
int	is_valid_right(t_token *token);
int	is_valid_t_pipe(t_token *token);


#endif
