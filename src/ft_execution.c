/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 23:42:10 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/24 23:42:14 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
		dprintf(fd_err, "args[0] = %s \n",args[0]);
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
		dprintf(fd_err, "Errorrr \n");
		exit (0);
	}
	return (-1);
}

///*** Check if cmd is builtens and splite
void		ft_split_cmd(int fork_it, t_pipes *st_pipes, char ***env)
{
	int pid;
	int i;
	int tmp[3];
	
	pid = 0;
	i = -1;

	/// Save STD_*
	while (++i < 3)
		tmp[i] = dup(i);
	/// Call Parser : to  read token and fill st_redi
	if (!(ft_parse_cmd(st_pipes) == PARSE_KO))
	{
		if (ft_check_built(st_pipes->args, env) != 1) /// in case of Builtens
		{
			if (fork_it == 1)
				pid = fork();
			if (pid == 0)	/// Execute cmd
			{
				if (ft_cmd_exec(st_pipes->args, *env) == -1)
					ft_print_error(CMD_NF, "21sh: ", (st_pipes->args)[0], 0); /// Command not found
			}
			if (pid != 0)
				wait(NULL);
		}
	}
	while (st_pipes->st_redir)
	{
		if (st_pipes->st_redir->fd_des != -1)
		{
			dprintf(fd_err, "fd to close = %d\n",st_pipes->st_redir->fd_des);
			close(st_pipes->st_redir->fd_des);
		}
		st_pipes->st_redir = st_pipes->st_redir->next;
	}
	/// Resete STD_*
	i = -1;
	while (++i < 3)
	{
		dup2(tmp[i], i);
		close(tmp[i]);
	}
}
///*** Check if Command builtens
int			ft_check_built(char **arg, char ***env)
{
	int		rtn;

	rtn = 0;
	if (*arg == NULL)
		return (-1);
	if (ft_strcmp(arg[0], "exitt") == 0)
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
int		ft_call_cmdss(char *str_arg, char ***environ)
{
	char		**args_pipe;
	t_pipes		*st_pipes;
	t_pipes		*st_temp;
	
	/// Split with PIPE |
	args_pipe = ft_str_split_q(str_arg, "|");

	/// Fill list st_pipes
	st_pipes = ft_strr_list(args_pipe);
	st_temp = st_pipes;
	while (st_temp)
	{
		/// split cmd with whitespace
		st_temp->args = ft_str_split_q(st_temp->cmd, " ");
		// Call Lexer and return list of tokens
		st_temp->st_tokens = ft_lexer(st_temp->args);

		/// Check error from created tokens
		if (ft_error_redir(st_temp->st_tokens))
		{
			/// free st_pipes -> tokens -> args
			ft_clear_cmds(st_pipes);
			return (-1);
		}
		st_temp = st_temp->next;
	}

	if (args_pipe != NULL && args_pipe[0] != NULL && args_pipe[1] != NULL) /// exist pipe in cmds
		ft_apply_pipe(st_pipes, environ);
	else
		ft_split_cmd(1, st_pipes, environ);

	ft_strrdel(args_pipe);
	return (1);
}

void		ft_clear_tokens(t_tokens *st_tokens)
{
	t_tokens *st_temp;

	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		st_temp = st_tokens;
		ft_strdel(&(st_tokens->value));
		st_tokens = st_tokens->next;
		(st_temp != NULL) ? free(st_temp) : NULL;
	}
}

void		ft_clear_cmds(t_pipes *st_pipes)
{
	t_pipes *st_temp;

	while (st_pipes)
	{
		st_temp = st_pipes;
		/// free args
		ft_strrdel(st_pipes->args);
		/// free cmd
		ft_strdel(&(st_pipes->cmd));
		/// free st_tokens
		ft_clear_tokens(st_pipes->st_tokens);
		st_pipes = st_pipes->next;
		(st_pipes != NULL) ? free(st_pipes) : NULL;
	}
}