/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:39 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/26 17:15:55 by fboumell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//returns 
# define SUCCESS 0
# define FAILURE -1

// tokens
# define L_RED 1
# define R_RED 2
# define DL_RED 3
# define DR_RED 4
# define D_QUOTE 5
# define S_QUOTE 6
# define WORD 7
# define T_PIPE 8
# define VAR_WORD 9

//colors 
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[0;36m"
# define RED "\033[4;31m"
# define RESET "\033[0m"

//prompt 
# define PROMPT "Minishell🌌 > "

//signal
# define HEREDOC_IGN 60
# define HEREDOC    61

#endif
