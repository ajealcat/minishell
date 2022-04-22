/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:56:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/22 14:44:00 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. lancer un '>'--> readline
2. read chaque entre et la reecrire 
3. comparer a notre char *value
4. stocker tout ce qu il y a dans un fichier cache ou idk
5 renvoyer les fichier cache en std_in pour la prochaine commande 

fork
afficher prompt avec readline et comparer la ligne avec delimitateur
mettre ce qui est ecrit dans un buffer avec retour a la ligne et join a hque fois
expandre les var environnement dans le here here_doc
*/

int	here_doc(char *value)
{
	int		fd_heredoc;
	pid_t	child_cmd;
	char	*ret_heredoc;
	char	*tmp;

	fd_heredoc = 0;
	// child_cmd = fork();
	// secure_child(child_cmd);
	// if (child_cmd == 0)
	// 	ret_heredoc = create_heredoc();
	while (1)
	{
		tmp = readline(">");
		if (strncmp(ret_heredoc, value, ft_strlen(value)) == 0)
			break ;
		tmp = read(0, )
	waitpid(child_cmd, &status, 0);
	return (fd_heredoc);
}
