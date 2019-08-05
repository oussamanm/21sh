/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:40:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/24 23:40:17 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

/*
**	Function PIPES 
*/
void		ft_close_pipes(t_pipes *st_pipes)
{
	while (st_pipes != NULL)
	{
		if (st_pipes->fds[0] != 0)
			close(st_pipes->fds[0]);
		if (st_pipes->fds[1] != 0)
			close(st_pipes->fds[1]);
		st_pipes = st_pipes->next;
	}
}
void		ft_create_pipes(t_pipes *st_pipes)
{
	t_pipes *st_head;
	int		fds[2];

	st_head = st_pipes;
	while (st_pipes->next != NULL)
	{
		if (pipe(fds) == -1)
			ft_err_exit("Error in Pipe Function \n");
		if (st_pipes == st_head)
			st_pipes->fds[0] = fds[0];
		st_pipes->fds[1] = fds[1];
		if (st_pipes->next != NULL)
			st_pipes->next->fds[0] = fds[0];
		st_pipes = st_pipes->next;
		if (st_pipes->next == NULL)
			st_pipes->fds[1] = fds[1];
	}
}
void		ft_apply_pipe(t_pipes *st_pipes, char ***environ)
{
	t_pipes *st_head;
	int parent;
	int child;

	st_head = st_pipes;
	/// Create child , to exec the last cmd and the other cmds
	if ((parent = fork()) == -1)
		ft_err_exit("Error in Fork \n");

	/// Initiale Pipes_line
	(parent == 0) ? ft_create_pipes(st_pipes) : NULL;

	while (parent == 0 && st_pipes != NULL)
	{
		/// Create other Childs
		if ((child = fork()) == 0)
		{
			/// Duplcating STD_IN on Read end of pipe
			if (st_pipes != st_head && dup2(st_pipes->fds[0] , 0) == -1)
				ft_putendl_fd("Error in dub STD_IN", 2);
			/// Duplcating STD_OUT on Write end of pipe
			if (dup2(st_pipes->fds[1] , 1) == -1)
				ft_putendl_fd("Error in dub STD_OUT", 2);
			/// Close all fds
			ft_close_pipes(st_head);
			// Execve
			ft_split_cmd(0, st_pipes, environ);
			exit(0);
		}
		st_pipes = st_pipes->next;
		if (st_pipes->next == NULL) /// parent_child
		{
			/// Duplcating STD_IN on Read end of pipe
			if (dup2(st_pipes->fds[0] , 0) == -1)
				ft_putendl_fd("Error in dub STD_IN", 2);
			/// Close all fds
			ft_close_pipes(st_head);	
			/// Execve
			ft_split_cmd(0, st_pipes, environ);
			exit(0);
		}
	}
	if (parent > 0)
		wait(NULL);
}
