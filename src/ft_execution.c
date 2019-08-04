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
#include "read_line.h"

/*
** Function Execution
*/


///*** Check redirection
int			ft_check_redi(t_pipes *st_pipes)
{
	t_tokens *st_temp;

	if (st_pipes == NULL || st_pipes->st_tokens == NULL)
		return (-1);
	st_temp = st_pipes->st_tokens;
	while (st_temp)
	{
		if (st_temp->token < 0)
			return (1);
		st_temp = st_temp->next;
	}
	return (0);
}

///*** Execute Command 
int			ft_cmd_exec(t_pipes *st_pipes, char **env)
{
	char	*str_arg;

	str_arg = NULL;
	if (st_pipes->args == NULL || st_pipes->args[0] == NULL)
		return (-2);
	/// Check Error : perm , no sush , ...
	if (!ft_check_char(st_pipes->args[0], '/'))
		str_arg = ft_find_path((st_pipes->args)[0], env);
	else
	{
		str_arg = ft_strdup(st_pipes->args[0]);
		if (access(str_arg, F_OK) != 0)
			ft_print_error(FIL_NS, NULL, str_arg, 2);
		else if (str_arg && access(str_arg, X_OK) != 0)
			ft_print_error(FIL_PD, NULL, str_arg, 2);
	}
	if (str_arg != NULL)
	{
		execve(str_arg, st_pipes->args, env);
		ft_strdel(&str_arg);
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
	///************* in case : Builtens
	if (st_pipes != NULL && ft_check_built((st_pipes->args)[0]))
	{
		/// Save STD_*
		while (++i < 3)
			tmp[i] = dup(i);
		/// Call builtens
		if (ft_call_built(st_pipes, env) == REDI_KO)
			return ;
		/// Resete STD_*
		i = -1;
		while (++i < 3)
			if (dup2(tmp[i], i) == -1 || close(tmp[i]) == -1)
				ft_putendl_fd("Error in dup or close \n", 2); // Dont exit
		return ;
	}

	///************* in case : cmd , Create new Child process
	if (fork_it == 1 && (pid = fork()) == -1)
		ft_err_exit("Error in Fork new process \n");
	if (pid == 0)
	{
		if (ft_check_redi(st_pipes)) /// Check if exist redirection
			if (ft_parse_cmd(st_pipes) == PARSE_KO)
				return ;
		if (!ft_strcmp(st_pipes->args[0], "echo"))							/// Builten ECHO (executed in child)
			ft_buil_echo(st_pipes->args);
		else
			if (ft_cmd_exec(st_pipes, *env) == -1)							/// Execute cmd
				ft_print_error(CMD_NF, "21sh: ", (st_pipes->args)[0], 0);	/// Command not found
		exit(0);
	}
	if (pid > 0)
	{
		g_sign = 1;
		wait(NULL);
		g_sign = 0;
	}
}

///*** Call Builtens (close fds of redirection)
int			ft_call_built(t_pipes *st_pipes, char ***env)
{
	int		rtn;

	rtn = 0;
	if (st_pipes == NULL || st_pipes->args == NULL)
		return (-1);
	/// Call Parser : to  read token and fill st_redi
	if (ft_check_redi(st_pipes)) /// Check if exist redirection
		if (ft_parse_cmd(st_pipes) == PARSE_KO)
			return (REDI_KO);
	/// Close all fds opned
	while (st_pipes->st_redir != NULL)
	{
		if (st_pipes->st_redir->fd_des != -1)
			close(st_pipes->st_redir->fd_des);
		st_pipes->st_redir = st_pipes->st_redir->next;
	}
	if (ft_strcmp((st_pipes->args)[0], "exit") == 0)
	{
		ft_strrdel(*env);
		ft_clear_readline_struct();
		ft_clear_cmds(st_pipes);
		exit(0);
	}
	if (ft_strcmp((st_pipes->args)[0], "env") == 0 && (rtn = 1))
		ft_buil_env(&(st_pipes->args)[1], env);
	if (ft_strcmp((st_pipes->args)[0], "setenv") == 0 && (rtn = 1))
		ft_buil_setenv(&(st_pipes->args)[1], env);
	if (ft_strcmp((st_pipes->args)[0], "unsetenv") == 0 && (rtn = 1))
		ft_buil_unsetenv(st_pipes->args[1], env);
	if (ft_strcmp((st_pipes->args)[0], "cd") == 0 && (rtn = 1))
		ft_buil_cd(&(st_pipes->args)[1], env);
	return (rtn);
}

///*** Check if Command builtens
int			ft_check_built(char *arg)
{
	int		rtn;

	rtn = 0;
	if (arg == NULL)
		return (-1);
	if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "env"))
		rtn++;
	else if (!ft_strcmp(arg, "setenv") || !ft_strcmp(arg, "unsetenv"))
		rtn++;
	else if (!ft_strcmp(arg, "cd"))
		rtn++;
	return (rtn);
}

///*** Check if there is a pipe
int		ft_call_cmdss(char *str_arg, char ***environ)
{
	char		**args_pipe;
	t_pipes		*st_pipes;
	t_pipes		*st_temp;
	
	if (str_arg == NULL)
		return (-1);
	/// Split with PIPE |
	args_pipe = ft_str_split_q(str_arg, "|");
	/// Fill list st_pipes
	st_pipes = ft_strr_list(args_pipe);
	(args_pipe) ? free(args_pipe) : NULL;
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
	if (st_pipes != NULL && st_pipes->next != NULL) /// exist pipe in cmds
		ft_apply_pipe(st_pipes, environ);
	else
		ft_split_cmd(1, st_pipes, environ);
	ft_clear_cmds(st_pipes);
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
		/// free old node
		free(st_temp);
	}
}