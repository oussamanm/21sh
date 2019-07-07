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

static void	ft_call_cmd(char **str_arg, char ***environ)
{
	char		**argv;
	int			rtn;

	argv = ft_str_split_q(str_arg, " \t");
	/// Correct Args
	ft_corr_args(&argv[1], *environ);
	/// Check if cmd is Builtin
	rtn = ft_check_built(argv, environ);
	/// Call cmd from system
	rtn = (rtn == 0) ? ft_call_child(argv, *environ, 0) : rtn;
	(rtn == -1) ? ft_print_error(CMD_NF, argv[0], "", 0) : NULL;
	ft_strrdel(argv);
}

int			ft_call_child(char **argv, char **env, int bl_path)
{
	pid_t	childpid;
	char	*str_arg;

	str_arg = NULL;
	childpid = fork();
	if (childpid == 0)
	{
		if (bl_path == 0 && !ft_check_char(argv[0], '/'))
			str_arg = ft_find_path(argv[0], env);
		else
		{
			str_arg = ft_strdup(argv[0]);
			if (access(str_arg, F_OK) != 0 && ++childpid)
				ft_print_error(FIL_NS, NULL, str_arg, 2);
			else if (str_arg && access(str_arg, X_OK) != 0 && ++childpid)
				ft_print_error(FIL_PD, NULL, str_arg, 2);
			(childpid != 0) ? exit(0) : NULL;
		}
		(str_arg != NULL) ? execve(str_arg, argv, env) : ft_strdel(&str_arg);
		ft_print_error(CMD_NF, NULL, argv[0], 0);
		exit(0);
	}
	wait(0);
	free(str_arg);
	return (0);
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
			ft_move_cur("DO", 0, ((st_dimen->len_arg + 2) / st_dimen->nbr_cln) - (st_dimen->index_c / st_dimen->nbr_cln));
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

	glb = 0;
	/// Error debug
	ft_intia_err("/dev/ttys000");
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
				ft_call_cmd(&args_cmd[i++], &environ);
		ft_strrdel(args_cmd);
		ft_strdel(&str_arg);
	}
	ft_strrdel(environ);
	return (0);
}