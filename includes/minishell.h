/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:19:05 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/10 18:47:17 by ajearuth         ###   ########.fr       */
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
} t_token;

typedef struct
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
void init_data(t_data *data);

	/* parse.c */
int parse(t_data *data);
char	*ft_strtrim(const char *s1, const char *set);

	/* protection_quote.c */
int check_quotes(char *token);

	/* check_parse.c */
int	unclose_quote(char *str);
int	checker_red(t_token *token);

//int	check_slash(char *token);
size_t	ft_strlen(const char *str);

	/* category */ 
int	token_word(t_token *token);

	/* token_list.c */
void	init_list(dblist *list);
void	free_list(dblist **list);
int add_list(t_token *node);
int create_node(char *str, int category, t_token *token);

	/* is_it_available.c */

int	is_valid_left(t_token *token);
int	is_valid_right(t_token *token);
int	is_valid_t_pipe(t_token *token);


#endif
