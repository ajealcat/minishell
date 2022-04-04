/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_multipipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajearuth <ajearuth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:11:12 by ajearuth          #+#    #+#             */
/*   Updated: 2022/04/04 16:06:12 by ajearuth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	make_exec_pipe(t_token *list, char **envp)
{
	t_token *tmp_list;
	pid_t	child_cmd;
	t_path	*our_path;
	int		**fd;
	int		count;
	int		i;
	int 	j;
	int		k;

	tmp_list = list;
	count = how_much_pipe(list); 
	printf("count = %d\n", count);
	fd = malloc(sizeof(int *) * (count + 2));
	if (fd == 0)
		return (FAILURE);
	i = -1;
	while (++i < (count + 2))
		fd[i] = malloc(sizeof(int) * 2);
	//pipe(fd);
	i = 0;
	while (i < (count + 2))
	{
		pipe(fd[i]);
		if (pipe(fd[i]) == -1)
			perror("Pipe");
		++i;
	}
	i = 0;
	k = 0;
	j = 0;
	while (i <= count)
	{
		our_path = init_path2(envp, &tmp_list);
		if (check_path(our_path) == FAILURE)
		{
			free_our_path(our_path);
			ft_putstr_fd("Command not found\n", 2);
			return (FAILURE);
		}
		child_cmd = fork();
		if (child_cmd < 0)
		{
			perror("Fork");
			return (FAILURE);
		}
		if (child_cmd == 0)
		{
			if (i == 0)
			{
				for (j = 0; j < (count + 2); j++) 
				{
                	if (i != j) 
                	    close(fd[j][0]);
                	if (i + 1 != j) 
                	    close(fd[j][1]);
				}
				dup2(fd[i + 1][1], 1);
			}
			else if (i == count)
			{
				for (j = 0; j < (count + 2); j++)
				{
                	if (i != j) 
                	    close(fd[j][0]);
                	if (i + 1 != j)
                	    close(fd[j][1]);
				}
				if (dup2(fd[i][0], 0) == -1)
				{
					printf("ERROR\n");
					return (FAILURE);
				}
			}
			else
			{
				for (j = 0; j < (count + 2); j++) 
				{
                if (i != j) 
                    close(fd[j][0]);
                if (i + 1 != j) 
                    close(fd[j][1]);
                }
				dup2(fd[i][0], 0); // 0 0
				dup2(fd[i + 1][1], 1); // 1 1 
			}
			// close(fd[i][1]);
			// close(fd[i][0]);
			cmd_execute(our_path);
		}
		/*if (i < count && count > 1)
			k++;
		printf("k = %d\n", k);*/
		 i++;
	}
	for (j = 0; j < (count + 2); j++) 
	{
    	if (i != j) 
    	    close(fd[j][0]);
    	if (i + 1 != j) 
    	    close(fd[j][1]);
	}
	close(fd[i][0]);
	close(fd[0][1]);
	j = 0;
	while (j <= count)
	{
		waitpid(child_cmd, 0, 0);
		j++;
	}
	free_our_path(our_path);
	return (0);
}


int	how_much_pipe(t_token *list)
{
	int			count;
	t_token		*tmp;

	count = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == t_pipe)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
