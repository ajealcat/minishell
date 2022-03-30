/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:33:50 by ajearuth          #+#    #+#             */
/*   Updated: 2022/03/30 18:31:01 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_token *list)
{
	list->type = 0;
	list->value = NULL;
	list->next = NULL;
	list->prev = NULL;
}

void	init_data(t_data *data)
{
	data->buf = NULL;
	data->str_trimed = NULL;
	data->i = 0;
}
/*
void	init_ofa(t_oneforall *ofa, t_token *list, t_data *data)
{
	ofa->str_ofa = NULL;
	ofa->list = list;
	ofa->data = data;
	ofa->i = 0;
}*/

t_path	*init_path(char **envp, t_token *list)
{
	t_path	*our_path;
	char	*tmp;
	int		i;

//	printf("Im in init path\n");
	i = 0;
	our_path = malloc(sizeof(t_path));
	if (!our_path)
		return (NULL);
	our_path->envp = envp;
	our_path->find_path = getenv("PATH");
	our_path->option_cmd = get_option_cmd(list);
	our_path->my_path = ft_split((const char *)our_path->find_path, ':');
	pipe(our_path->pipefd);
//	printf("Value before boucle %s\n", list->value);
	while (our_path->my_path[i])
	{
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], "/");
		free(tmp);
		tmp = our_path->my_path[i];
		our_path->my_path[i] = ft_strjoin(our_path->my_path[i], list->value);
		free(tmp);
		i++;
	}
	return (our_path);
}

t_forpipe	*init_forpipe(void)
{
	t_forpipe	*forpipe;
	pid_t		child_cmd;

	forpipe = malloc(sizeof(t_forpipe));
	if (!forpipe)
		return (NULL);
	// if (pipe(pipefd) == -1)
	// {
	// 	perror("Pipe");
	// 	return (FAILURE);
	// }
	child_cmd = fork();
	// if (child_cmd < 0)
	// {
	// 	perror("Fork");
	// 	return (FAILURE);
	// }
	pipe(forpipe->pipefd);
	forpipe->child_cmd = child_cmd;
	return (forpipe);
}
