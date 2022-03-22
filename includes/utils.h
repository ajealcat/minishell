/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:39 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/22 16:15:32 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//returns 
# define SUCCESS 0
# define FAILURE -1

// tokens
# define l_red 1
# define r_red 2
# define dl_red 3
# define dr_red 4
# define d_quote 5
# define s_quote 6
# define word 7
# define t_pipe 8
# define var 9


//colors 
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[0;36m"
# define RED "\033[4;31m"
# define RESET "\033[0m"

//prompt 
# define PROMPT "\033[0;35mMinishell\033[0m 🌌 > "

#endif
