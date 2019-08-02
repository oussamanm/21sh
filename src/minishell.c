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
#include "../includes/termcap.h"

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

char		*get_next_split(char *cmd, char *split)
{
	char	*keys[6] = {";", "||", "&&", "&", "|", NULL};
	int		cpt;
	int		i;

	//if (keys == NULL)
	//	keys = (char[5][3]){";", "||", "&&", "&", NULL};
	i = -1;
	cpt = 0;
	while (keys[++i])
	{
		if (ft_strequ(keys[i], split))
			cpt = 1;
		if (cpt && ft_strstr(cmd, keys[i]))
			return (keys[i]);
	}
	return (NULL);
}

void		ft_parser(char *cmd, char *split, char ***env)
{
	int i;
	char **args;
	char *next;

	if (split == NULL)
		return ;
	if (ft_strequ(split, "|"))
		ft_call_cmdss(cmd, env);
	else
	{
		args = ft_strsplit_by_arr(cmd, split);
		i = -1;
		while (args[++i])
		{

			//dprintf(fd_err, "\n args[%d] : %s | split : %s \n", i, args[i], split);
			if ((next = get_next_split(args[i], split)))
				ft_parser(args[i], next, env);
			else
				ft_call_cmdss(args[i], env);
		}
		ft_strrdel(args);		
	}
}

int			ft_parse_error(char *str_cmds)
{
	/// check ; error
	if (ft_error_separ(str_cmds, ';'))
	{
		ft_putstr_fd("syntax error near unexpected token `;' \n", 2);
		return (1);
	}
	/// check | error
	if (ft_error_separ(str_cmds, '|'))
	{
		ft_putstr_fd("syntax error near unexpected token `| hello' \n", 2);
		return (1);
	}
	return (0);
}

int			main(void)
{
	extern char	**environ;
	char		*str_cmds;
	int			i;

	/// Initail error 
	ft_intia_err("/dev/ttys001");
	
	///Initial interface : tgetent
	if (tgetent(NULL, getenv("TERM")) != 1)
		ft_err_exit("Error tgetent ,may variable TERM not valid! \n");
	///Call functions signal
	ft_call_signal();
	/// Duplicate environ
	environ = ft_strr_dup(environ, ft_strrlen(environ));
	while (1337)
	{
		i = 0;
		// fill str_arg with command Entred And print prompt
		if ((str_cmds = set_line(0, environ)) != NULL)
		{
			/// Check all error ; | redir 
			if (ft_parse_error(str_cmds))
			{
				/// print prompt
				ft_strdel(&str_cmds);
				continue ;
			}
			/// Correction args : Expansions + Correct Quoting
			str_cmds = ft_corr_args(str_cmds, environ);
			/*
			///  Splite line entred with {;,&&,||,&} and Execute cmds
			//ft_parser(str_cmds, ";", &environ);*/
			ft_call_cmdss(str_cmds, &environ);
			ft_strdel(&str_cmds);
		}
	}
	ft_strrdel(environ);
	return (0);
}

void		exit_shell(char **env)
{
	UNUSED(env);
	//ft_strrdel(env);
	enable_term();
	exit(0);
}
