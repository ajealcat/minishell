/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:19:05 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/22 17:06:12 by ajearuth         ###   ########.fr       */
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
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char			*buf;
	char			*str_trimed;
	int				i;
}	t_data;

	/* prompt.c */
int		print_prompt(t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

	/* init.c */
void	init_token(t_token *token);
void	init_data(t_data *data);

	/* parse.c */
t_token	*parse(t_token *list, t_data *data);
char	*ft_strtrim(const char *s1, const char *set);
t_token	*check_category(t_token *list, t_data *data);

	/* protection_quote.c */
int		check_quotes(char *token);
int		unclose_quote(char *str);

	/* utils.c */
int		ft_strlen_word(char *str);
int		ft_strlen_dollar(char *str);
int		ft_strlen_between_quotes(char *str, int count, char quote);
int		check_sep_for_word(int c);
int		go_for_word(int c);
int		ft_strlen_encore(char *str);

int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *str, unsigned int start, size_t len);

	/* token_others.c */
t_token	*r_redirect(t_token *list, t_data *data);
t_token	*l_redirect(t_token *list, t_data *data);
t_token	*token_word(t_token *list, t_data *data);
t_token	*token_dollar(t_token *list, t_data *data);

	/* token_quote.c */
int		count_quote(char *str, char quote);
t_token	*token_between_dquote(t_token *list, t_data *data);
t_token	*token_between_squote(t_token *list, t_data *data);

	/* token_list.c */
t_token	*add_list(t_token *list, t_token *new_token);
t_token	*create_node(t_token *list, char *str, int category);

	/* is_it_available.c */
int		checker_red(t_token *token);
int		is_valid_left(t_token *list);
int		is_valid_right(t_token *list);
int		is_valid_t_pipe(t_token *list);

	/* free.c */
void	free_list(t_token **list);
void	ft_putstr_fd(char *str, int fd);

#endif
