/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:56:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/22 17:31:18 by ajearuth         ###   ########.fr       */
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

int	make_here_doc(char *buffer, int fd_heredoc_in, int fd_heredoc_out)
{
	write(fd_heredoc_out, buffer, ft_strlen(buffer));
	close(fd_heredoc_out);
	fd_heredoc_in = open(".heredoc", O_RDONLY);
	if (fd_heredoc_in < 0)
		return (FAILURE);
	return (fd_heredoc_in);
}

int	here_doc(char *eof)
{
	int		fd_heredoc_out;
	int		fd_heredoc_in;
	pid_t	child_cmd;
	char	*line;
	char	*tmp;
	char	*buffer;

	fd_heredoc_out = 1;
	fd_heredoc_in = 0;
	buffer = ft_strdup("");
	child_cmd = fork();
	secure_child(child_cmd);
	fd_heredoc_out = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_heredoc_out < 0)
		return (FAILURE);
	if (child_cmd == 0)
	{
		line = readline(">");
		while (1)
		{
			// signal(SIGINT, gestion_signaux);
			// signal(SIGQUIT, gestion_signaux);
			if (strncmp(line, eof, ft_strlen(eof)) == 0)
				break ;
			tmp = buffer;
			buffer = ft_strjoin(tmp, line);
			free(tmp);
			tmp = buffer;
			buffer = ft_strjoin(tmp, "\n");
			free(line);
			line = readline(">");
		}
		fd_heredoc_in = make_here_doc(buffer, fd_heredoc_in, fd_heredoc_out);
		free(buffer);
		free(line);
	}
	waitpid(child_cmd, 0, 0);
	unlink(".heredoc");
	return (fd_heredoc_in);
}
