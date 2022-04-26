/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboumell <fboumell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:56:47 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/26 14:32:09 by fboumell         ###   ########.fr       */
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

int	here_doc(char *eof, t_pipex *multi, t_data *data)
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
	signal(SIGSEGV, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child_cmd = fork();
	secure_child(child_cmd);
	fd_heredoc_out = open("objs/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_heredoc_out < 0)
		return (FAILURE);
	if (child_cmd == 0)
	{	
		signal(SIGSEGV, heredoc_signaux);
		signal(SIGINT, heredoc_signaux);
		signal(SIGQUIT, heredoc_signaux);
		line = readline(">");
		while (line)
		{
			if (strncmp(line, eof, ft_strlen(eof)) == 0)
				break ;
			tmp = buffer;
			buffer = ft_strjoin(tmp, line);
			free(tmp);
			free(line);
			tmp = buffer;
			buffer = ft_strjoin(tmp, "\n");
			free(tmp);
			line = readline(">");
		}
		fd_heredoc_in = make_here_doc(buffer, fd_heredoc_in, fd_heredoc_out);
		free(buffer);
		free(line);
		free_exit(multi->list, data, 0, multi);
	}
	waitpid(child_cmd, 0, 0);
	if (buffer)
		free(buffer);
	unlink("objs/.heredoc");
	return (fd_heredoc_in);
}
