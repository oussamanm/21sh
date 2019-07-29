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
		execve(str_arg, args, env);
		ft_strdel(&str_arg);
		return (0);
	}
	return (-1);
}
///*** Check if cmd is builtens and splite
void		ft_split_cmd(int fork_it, t_pipes *st_pipes, char ***env)
{
	char **args;
	int pid;
	
	pid = 0;
	args = ft_str_split_q(st_pipes->cmd, " \t");
	/// call ft_parse_cmd : Lexer and parser
	ft_parse_cmd(st_pipes, args);

	/// Check Builtens
	if (ft_check_built(args, env) != 1) // in case of builtens
	{
		if (fork_it == 1)
			pid = fork();
		if (pid == 0 && ft_cmd_exec(args, *env) == -1)
			ft_print_error(CMD_NF, "21sh: ", *args, 0); /// Command not found
		if (pid != 0)
			wait(NULL);
	}
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
	t_pipes		*st_pipes;
	
	args_pipe = ft_str_split_q(*str_arg, "|");
	st_pipes = ft_strr_list(args_pipe);
	if (args_pipe != NULL && args_pipe[0] != NULL && args_pipe[1] != NULL) /// exist pipe in cmds
		ft_apply_pipe(st_pipes, environ);
	else
		ft_split_cmd(1, st_pipes, environ);

	ft_strrdel(args_pipe);
}