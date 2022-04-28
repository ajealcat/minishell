/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:19:05 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/28 22:08:54 by ajearuth         ###   ########.fr       */
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

extern int	g_status;

typedef struct s_env
{
	char			**envp;
	char			**av;
}	t_env;

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
	char			*find_path;
	char			**option_cmd;
	char			**my_path;
}	t_path;

typedef struct s_data
{
	char			*buf;
	char			*str_trimed;
	int				i;
	t_env			*our_env;
}	t_data;

typedef struct s_pipex
{
	int				**fd;
	int				count;
	int				i;
	int				j;
	int				fd_file_out;
	int				fd_file_in;
	t_token			*list;
}	t_pipex;

typedef struct s_hdoc
{
	t_data	*data;
	int		fd_heredoc_out;
	int		fd_heredoc_in;
	int		fd[2];
	char	*buffer;
	char	*line;
	char	*eof;
}	t_hdoc;

	/* prompt.c */
void	free_data_buf(t_data *data);
void	free_data(t_data *data);
int		print_prompt(t_data *data);

	/* init.c */
void	init_token(t_token *token);
void	init_data(t_data *data);
t_pipex	*init_pipex(t_token *list);
t_path	*init_path(t_env *our_env, t_token *list);
t_path	*init_path2(t_env *our_env, t_token **tmp);

	/* parse.c */
t_token	*parse(t_token *list, t_data *data);
t_token	*check_category(t_token *list, t_data *data);
int		does_list_contain_pipe(t_token *list);
int		parsing_for_exec(t_token *list, t_data *data);
int		parse_builtin(t_token *list, t_data *data, t_pipex *multi);

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
int		is_maj(char *str);

	/* token_quote.c */
t_token	*reparse_dquote(t_token *list, char *str, t_data *data);
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
char	*gojo_expand(char *tmp, t_env *our_env);
char	*find_var(t_env *our_env, char *tmp);

	/* signaux.c */
void	check_sig(int sig);
void	gestion_signaux(int sig);
void	heredoc_signaux(int sig);

	/* exec_access.c */
char	**reduce_goc(t_token *list);
char	**get_option_cmd(t_token *list);
char	**get_option_cmd2(t_token *list);
char	**reduce_goc_bis(t_token *tmp, t_token *list, int i, int j);
// char	*find_path(t_token *list, char **envp);

	/* free.c */
void	free_list(t_token **list);
void	free_fromstart(t_token **list);
void	free_split(char **cmd);
void	free_our_path(t_path *our_path);
void	free_multi(t_pipex *multi);
void	free_our_env(t_env *our_env);

	/*  security.c */
int		secure_child(pid_t child_cmd);
int		path_not_found(t_path *our_path, t_pipex *multi);
int		secure_fd(int fd);

	/* exc_mutipipe.c */
int		make_exec_pipe(t_token *list, t_data *data);
int		how_much_pipe(t_token *list);
void	close_fd(int i, int count, int **fd);
int		make_child(pid_t child, t_pipex *multi, t_path *our_path, t_data *data);
t_token	*increase_tmp_list(t_token **tmp_list);

	/* exc_onecmd.c */
int		make_exec_word(t_token *list, t_data *data);
int		check_path(t_path *our_path);
int		cmd_execute(t_path *our_path);
int		set_up_fd(t_pipex *multi, t_data *data);

	/* builtin_cdpwd.c */
int		builtin_pwd(void);
void	back_home(char *pwd);
int		builtin_cd(t_token *list);
void	reduce_builtcd(char *oldpwd, char *pwd, char *pwd_ptr);
char	*move_pwd(char **av, char *pwd);

	/* builtin_echo.c */
int		printf_echo(char **av, int n);
int		builtin_echo(t_token *list);
int		check_flagn(char *av);

	/* utils_builtins.c */
int		count_av(char **av);
char	**create_arg(t_token *list);
char	**create_ourenv(char **tab);
int		ft_tablen(char **tab);
void	print_env(t_env *our_env);

	/* utils_builtins_bis.c */
void	reduce_builtexport(char **tmp, t_env *our_env, char *av);
int		is_builtin(t_token *list);
char	**create_arg2(t_token *list);
char	*glue_value(t_token *tmp);
char	**reduce_create_arg2(t_token *tmp, char **av);

	/* builtin_exit.c */
int		only_digit(char *av);
int		free_exit(t_token *list, t_data *data, int code, t_pipex *multi);
int		builtin_exit(t_token *list, t_data *data, t_pipex *multi);

	/* builtin_env.c */
int		builtin_env(t_env *our_env);

	/*other_cmd.c */
int		other_cmd(void);

	/* builtin_export.c */
int		is_var(t_env *our_env, char *tmp);
void	replace_value(t_env *our_env, char **tmp);
char	**create_value(t_env *our_env, char *av);
int		builtin_export(t_token *list, t_env *our_env);
void	norm_export(char **tmp, t_env *our_env, int i);

	/* builtin_unset.c */
int		builtin_unset(t_token *list, t_env *our_env);
char	**unset_copy(t_env *our_env, char **av, int count);
int		is_argument(char **av, char *env_var);

	/* redicrections.c */
int		reduce_check_red(t_token *tmp, t_pipex *multi, t_data *data, int value);
int		check_redirections(t_pipex *multi, t_data *data);
int		open_or_createfd(char *value, int nb);

	/* heredoc.c */

t_hdoc	*init_heredoc(char *eof);
int		free_heredoc(t_hdoc *heredoc);
int		here_doc(char *eof, t_pipex *multi, t_data *data);
int		make_here_doc(char *buffer, int fd_heredoc_in, int fd_heredoc_out);

	/* utils_exec.c */
void	wait_exec_pipe(t_pipex *multi, pid_t child_cmd);
void	reduce_make_child_one(t_pipex *multi);
void	reduce_make_child_two(t_pipex *multi);
void	reduce_make_child_three(t_pipex *multi);
void	reduce_vrreuumant(t_pipex *multi, t_data *data);

	/* utils_exec_word.c */
int		reduce_make_child_onecmd(t_pipex *multi, t_path *our_path);
int		check_path_failed(t_path *our_path, t_pipex *multi);
void	wait_onecmd(pid_t child_cmd, t_pipex *multi, t_path *our_path);
void	reduce_setupfd(t_pipex *multi);
int		exec_failed(t_pipex *multi, t_data *data, t_path *our_path);

	/* utils_init.c */
char	**reduce_init_path2(t_token **tmp_list, t_path *our_path);
int		**reduce_init_pipex(t_pipex *multi);
char	**my_path_slash(char **my_path, t_token *list);
char	**my_path_dot(char **my_path, t_token *list);
char	**my_path_current(t_path *our_path, t_token *list);

	/* utils_token.c */
t_token	*reduce_reparse_dquote(char *tmp, t_data *data, t_token *list);
t_token	*reduce_reparse_dquote2(int i, int j, char *str, t_token *list);
char	*reduce_token_btw_dquote(t_data *data, int size, int count, char *tmp);
char	*reduce_token_btw_squote(t_data *data, int size, int count, char *tmp);
t_token	*reduce_token_dollar(char *tmp, t_data *data, t_token *list);

	/* utils_heredoc.c */
void	boucle_line_heredoc(t_hdoc *heredoc, t_pipex *multi, t_data *data);
void	buffer_expand(t_hdoc *heredoc, t_data *data);

	/* utils_ter.c */
int		ft_strcmp(const char *s1, const char *s2);

#endif
