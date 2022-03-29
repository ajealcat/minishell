/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:19:05 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/29 18:31:56 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"
# include "libft.h"
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

typedef struct s_path
{
	char			**envp;
	char			*find_path; /* no need to free this one */
	char			**option_cmd;
	char			**my_path;
}	t_path;

typedef struct s_oneforall
{
	char	**str_ofa;
	int		i;
	t_token	*list;
	t_data	*data;
}	t_oneforall;

typedef struct s_data
{
	char			*buf;
	char			*str_trimed;
	int				i;
}	t_data;

	/* prompt.c */
int		print_prompt(t_data *data, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

	/* init.c */
void	init_token(t_token *token);
void	init_data(t_data *data);
t_path	*init_path(char **envp, t_token *list);

	/* parse.c */
t_token	*parse(t_token *list, t_data *data);
t_token	*check_category(t_token *list, t_data *data);
int		does_list_contain_pipe(t_token *list);
int		parsing_for_exec(t_token *list, char **envp);

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

	/* token_others.c */
t_token	*r_redirect(t_token *list, t_data *data);
t_token	*l_redirect(t_token *list, t_data *data);
t_token	*token_word(t_token *list, t_data *data);
t_token	*token_dollar(t_token *list, t_data *data);


	/* token_quote.c */
t_token	*reduce_fonction(char *str, char *tmp, int i, t_token *list);
t_token	*reparse_dquote(t_token *list, char *str);
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

	/* gojo_expand.c */
char	*gojo_expand(char *tmp);


	/* signaux.c */
void	gestion_signaux(int sig);

	/* exec_access.c */
char	**get_option_cmd(t_token *list);
char	*find_path(t_token *list, char **envp);

	/* free.c */
void	free_list(t_token **list);
void	free_split(char **cmd);
void	free_our_path(t_path *our_path);

/*  security.c */
int		secure_child(pid_t child_cmd);

/* crete_child */
int		make_exec_word(t_token *list, char **envp);
int		check_path(t_path *our_path);
void	cmd_execute(t_path *our_path);

/* exc_mutipipe */

int		make_exec_pipe(t_token *list, char **envp);

#endif
