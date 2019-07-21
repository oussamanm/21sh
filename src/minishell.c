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
//#include "termcap.h"
#include "../includes/termcap.h"

/* lst func
	void		ft_lst_print(t_pipes *lst, int i)
	{
		UNUSED(i);
		while (lst != NULL)
		{
			printf("Addresse is |%p| \t",lst);
			//if (i == 0 || i == 2)
			//printf("content is |%s| \n",lst->cmd);
			//if (i == 1 || i == 2)
			printf("fds is |%d|;|%d| \n\n",lst->fds[0],lst->fds[1]);
			lst = lst->next;
		}
	}
	int			ft_lst_count(t_pipes *lst)
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
*/

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
void		ft_apply_pipe(char **args_pipe, char ***environ)
{
	t_pipes *st_pipes;
	t_pipes *st_head;
	int parent;
	int child;

	st_pipes = ft_strr_list(args_pipe);
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
				ft_err_exit("Error in dub STD_IN");
			/// Duplcating STD_OUT on Write end of pipe
			if (dup2(st_pipes->fds[1] , 1) == -1)
				ft_err_exit("Error in dub STD_OUT");
			/// Close all fds
			ft_close_pipes(st_head);
			// Execve
			ft_split_cmd(st_pipes->cmd, environ);
		}
		st_pipes = st_pipes->next;
		if (st_pipes->next == NULL) /// parent_child
		{
			/// Duplcating STD_IN on Read end of pipe
			if (dup2(st_pipes->fds[0] , 0) == -1)
				ft_err_exit("Error in dub STD_IN");
			/// Close all fds
			ft_close_pipes(st_head);	
			/// Execve
			ft_split_cmd(st_pipes->cmd, environ);
		}
	}
	if (parent > 0)
		wait(NULL);
}


/*
** Function Execution
*/

///*** Execute Command
int			ft_cmd_exec(char **args, char **env)
{
	char	*str_arg;

	str_arg = NULL;
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
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
		return (0);
	}
	return (-1);
}
///*** Check if cmd is builtens and splite
void		ft_split_cmd(char *cmd, char ***env)
{
	char **args;

	if ((args = ft_str_split(cmd, " \t")) == NULL)
	{
		ft_putstr("Error NULL return of split \n");
		return ;
	}
	/// Check Builtens
	if (ft_check_built(args, env) != 1) // in case of builtens
		if (ft_cmd_exec(args, *env) == -1)
			ft_print_error(CMD_NF, "21sh: ", *args, 0); /// Command not found
	//exit(0);
}
///*** Check if Command builtens
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
///*** Check if there is a pipe
void		ft_call_cmdss(char **str_arg, char ***environ)
{
	char		**args_pipe;
	//pid_t		pid;
	
	args_pipe = ft_str_split_q(str_arg, "|");
	if (args_pipe != NULL && args_pipe[0] != NULL && args_pipe[1] != NULL) /// exist pipe in cmds
		ft_apply_pipe(args_pipe, environ);
	else
	{
		ft_split_cmd(*str_arg, environ);
	}
	ft_strrdel(args_pipe);
}

/*
** Initiale terminle attr , fill struct info and call function Read
*/
char		*set_line(int sig, char **env)
{
	static struct s_termcap	info;

	if (sig)
		ft_init_signal(sig, &info);
	else
	{
		disable_term();
		//if (get_col_pos() > 1)
		//	ft_putchar('\n');
		set_info_termcap(&info, get_prompt());
		ft_putstr(info.prompt);
		read_input(0, &info, env);
		enable_term();
		ft_putchar('\n');
		ft_strdel(&(info.prompt));
		return(info.content);
	}
	return (NULL);
}

int			main(void)
{
	extern char	**environ;
	char		**args_cmd;
	char		*str_cmds;
	int			i;

	///Initial interface : tgetent
	if (tgetent(NULL, getenv("TERM")) != 1)
		ft_err_exit("Error tgetent ,may variable TERM not valid! \n");
	///Call functions signal
	ft_call_signal();
	environ = ft_strr_dup(environ, ft_strrlen(environ));
	while (1337)
	{
		i = 0;
		// fill str_arg with command Entred || and print prompt
		if ((str_cmds = set_line(0, environ)) != NULL)
		{
			/// Split with ; multi command and call cmd
			args_cmd = ft_str_split_q(&str_cmds, ";");
			if (!ft_error_semic(str_cmds, args_cmd) || !ft_putstr("Syntax error\n")) /// Check error ; syntax
			{
				while (args_cmd != NULL && args_cmd[i] != NULL)
					ft_call_cmdss(&(args_cmd[i++]), &environ);
			}
			ft_strrdel(args_cmd);
			//ft_strdel(&str_cmds);
		}
	}
	//ft_strrdel(environ);
	return (0);
}

void			exit_shell(char **env)
{
	UNUSED(env);
	//ft_strrdel(env);
	enable_term();
	exit(0);
}
