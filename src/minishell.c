/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:54:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 18:10:24 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_lst_print(t_pipes *lst,int i)
{
	while (lst != NULL)
	{
		dprintf(fd_err, "Addresse is |%p| \t",lst);
		if (i == 0 || i == 2)
			dprintf(fd_err, "content is |%s| \t",lst->cmd);
		if (i == 1 || i == 2)
			dprintf(fd_err, "fds is |%d|;|%d| \n",lst->fds[0],lst->fds[1]);
		lst = lst->next;
	}
}

int		ft_lst_count(t_pipes *lst)
{
	int resu;

	resu = 0;
	while (lst != NULL)
	{
		resu++;
		lst = lst->next;
	}
	return (resu);
}


t_pipes		*ft_strr_list(char **args_pipe)
{
	t_pipes *st_pipes;
	t_pipes *head;

	st_pipes = NULL;
	while (*args_pipe)
	{
		if (st_pipes == NULL)
		{
			st_pipes = (t_pipes *)malloc(sizeof(*st_pipes));
			head = st_pipes;
		}
		st_pipes->cmd = *args_pipe;
		args_pipe++;
		if (*args_pipe != NULL)
		{
			st_pipes->next = (t_pipes *)malloc(sizeof(*st_pipes));
			st_pipes = st_pipes->next;
		}
		else
			st_pipes->next = NULL;
	}
	return (head);
}

void	ft_split_cmd(char *cmd, char **env)
{
	char **args;

	if ((args = ft_str_split(cmd, " \t")) == NULL)
	{
		ft_putstr("Error NULL return of split \n");
		return ;
	}
	ft_cmd_exec(args, env);
}


void	ft_call_cmdss(char **str_arg, char ***environ)
{
	char		**args_pipe;
	t_pipes		*st_pipes;
	int			i = 0;
	int			len;
	int			pid;
	int			fds[2];

	args_pipe = ft_str_split_q(str_arg, "|");
	st_pipes = ft_strr_list(args_pipe);

	len = ft_lst_count(st_pipes);
	//ft_lst_print(st_pipes, 2);

	while (st_pipes != NULL)
	{
		if (pipe(fds) == -1)
			ft_err_exit("Error in Pipe Function \n");
		st_pipes->fds[1] = fds[1];
		if (st_pipes->next != NULL)
			st_pipes->next->fds[0] = fds[0];
		if ((pid = fork()) == 0)
		{
			printf("Start with : fds[0] = %d and fds[1] = %d \n ", fds[0], fds[1]);
			/// Close unsed Read end of Child1
			if (i == 0 && close(st_pipes->fds[0]) == -1)
				perror("Error close read in child");
			
			//// *** Duplcating
				// pair even	// Duplcating STD_OUT on Write end of pipe
				// unpair odd 	// Duplcating STD_IN on Read end of pipe
		
			if (i != 0 && dup2(st_pipes->fds[0] , 0) == -1)
				perror("Error in dub STD_IN");

			if (dup2(st_pipes->fds[1] , 1) == -1)
				perror("Error in dub STD_OUT");
			else if (close(st_pipes->fds[1]) == -1)
				perror("Error in Close fds[0] in child 2");
			
			//execve(st_pipes->cmd, (char *[2]){args_pipe[0],"NULL"}, *environ);
			ft_split_cmd(st_pipes->cmd, *environ);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		st_pipes = st_pipes->next;
	}
	/*
		argv = ft_str_split_q(str_arg, " \t");

		/// Correct Args
		ft_corr_args(&argv[1], *environ);
		/// Check if cmd is Builtin
		rtn = ft_check_built(argv, environ);
		/// Call cmd from system
		rtn = (rtn == 0) ? ft_call_child(argv, *environ, 0) : rtn;
		(rtn == -1) ? ft_print_error(CMD_NF, argv[0], "", 0) : NULL;
		ft_strrdel(argv);
	*/
	ft_strrdel(args_pipe);
}


static void	ft_call_cmds(char **str_arg, char ***environ)
{
	char		**args_pipe;
	t_pipes		*st_pipes;
	int			*fds;
	int			i = 0;

	//int pid;
	int len;

	args_pipe = ft_str_split_q(str_arg, "|");
	st_pipes = ft_strr_list(args_pipe);

	len = ft_lst_count(st_pipes);
	i = 0;
	fds = (int *)malloc(sizeof(int) * ((len - 1) * 2));
	while (i < len - 1)
	{
		pipe(fds);
		i += 2;
	}
	pid_t childs[3];
	childs[0] = fork();
	if (childs[0] > 0)
		childs[1] = fork();
	i = -1;
	while (++i < len)
	{
		if (childs[i] == 0)
		{
			if (i == 0)
			{
				if (close(fds[0]) == -1)
					perror("Error close read in child");
				dup2(fds[1], 1);
				close(fds[1]);
			}
			else if (i > 0 && i < len - 1)
			{
				dup2(fds[0], 0);
				close(fds[0]);
				dup2(fds[1], 1);
				close(fds[1]);
			}
			else if (i == len - 1)
			{
				close(fds[1]);
				dup2(fds[0], 0);
				close(fds[0]);
			}
			execve(args_pipe[i], (char *[2]){args_pipe[0],"NULL"}, *environ);
		}
		else if (childs[i] > 0)
		{
			wait(NULL);
		}
		st_pipes = st_pipes->next;
	}
	ft_strrdel(args_pipe);
}

int			ft_cmd_exec(char **args, char **env)
{
	char	*str_arg;

	str_arg = NULL;
	/*if ((args = ft_str_split(cmd, " \t")) == NULL)
	{
		ft_putstr("Error NULL return of split \n");
		return (-1);
	}*/
	if (!ft_check_char(args[0], '/'))
		str_arg = ft_find_path(args[0], env);
	else
	{
		str_arg = ft_strdup(args[0]);
		if (access(str_arg, F_OK) != 0)
			ft_print_error(FIL_NS, NULL, str_arg, 2);
		else if (str_arg && access(str_arg, X_OK) != 0)
			ft_print_error(FIL_PD, NULL, str_arg, 2);
	}
	if (str_arg != NULL)
	{
		//printf("Hello in %s \n",str_arg);
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
	}
	return (-1);
}

int			ft_check_built(char **arg, char ***env)
{
	int		rtn;

	rtn = 0;
	if (*arg == NULL)
		return (-1);
	if (ft_strcmp(arg[0], "exit") == 0)
		kill(0, SIGQUIT);
	if (ft_strcmp(arg[0], "env") == 0 && (rtn = 1))
		ft_buil_env(&arg[1], env);
	if (ft_strcmp(arg[0], "setenv") == 0 && (rtn = 1))
		ft_buil_setenv(&arg[1], env, ft_strrlen(&arg[1]));
	if (ft_strcmp(arg[0], "unsetenv") == 0 && (rtn = 1))
		ft_buil_unsetenv(arg[1], env);
	if (ft_strcmp(arg[0], "echo") == 0 && (rtn = 1))
		ft_buil_echo(arg, *env);
	if (ft_strcmp(arg[0], "cd") == 0 && (rtn = 1))
		ft_buil_cd(&arg[1], env);
	return (rtn);
}


char		*ft_read_sh(int fd)
{
	t_dimen *st_dimen;
	char	*arg;
	int		temp;

	temp = 0;
	st_dimen = ft_init_dim();
	arg = ft_strnew(1);
	while (read(fd, &temp, 4) > 0)
	{
		if (temp == '\n')
		{
			//*c*//ft_move_cur("DO", 0, ((st_dimen->len_arg + 2) / st_dimen->nbr_cln) - (st_dimen->index_c / st_dimen->nbr_cln));
			ft_putstr("\n");
			break ;
		}
		if (ft_isprint(temp))	/// Printable input
			ft_print_char(&arg, temp, st_dimen);
		else  					/// NoNPrintable input
			ft_buttons(temp, &arg, st_dimen);
		temp = 0;
	}
	return (arg);
}

int			main(void)
{
	extern char	**environ;
	char		*str_arg;
	char		**args_cmd;
	t_termios	st_savedattr;
	int			i;

	/// Error debug
	//ft_intia_err("/dev/ttys005");
	// Initial interface
	ft_init_interf(&st_savedattr);
	// Initial signale
	ft_init_signal(0, &st_savedattr);

	environ = ft_strr_dup(environ, ft_strrlen(environ));
	while (1337)
	{
		i = 0;
		ft_putstr("$> ");
		// fill str_arg with command Entred
		str_arg = ft_read_sh(0);

		/// Split with ; multi command and call cmd
		args_cmd = ft_str_split_q(&str_arg, ";");
		if (!ft_error_semic(str_arg, args_cmd) || !ft_putstr("Syntax error\n")) /// Check error ; syntax
			while (args_cmd != NULL && args_cmd[i] != NULL)
				ft_call_cmds(&args_cmd[i++], &environ);
		ft_strrdel(args_cmd);
		ft_strdel(&str_arg);
	}
	ft_strrdel(environ);
	return (0);
}