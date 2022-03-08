/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fahima42 <Fahima42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:19:05 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/08 16:35:18 by Fahima42         ###   ########.fr       */
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

typedef struct s_data
{
    int count_sep;
    int i;
    char **token;
} t_data;


    /* prompt.c */
int print_prompt(void);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

    /* init.c */
void init_data(t_data *data);

/* parse.c */
int parse(char *buf, t_data *data);
char	**ft_split(const char *str, char c);

    /* protection_quote.c */
int	global_check(char *str);
int check_quotes(char *token);
int	check_slash(char *token);
size_t	ft_strlen(const char *str);

#endif
