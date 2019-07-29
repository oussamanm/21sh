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

char		*get_next_spli(char *cmd, char *split)
{
	char	*keys[5] = {";", "||", "&&", "&", NULL};
	int		cpt;
	int		i;

	//if (keys == NULL)
	//	keys = (char[5][3]){";", "||", "&&", "&", NULL};
	i = -1;
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

	if (split == NULL)
		return ;
	args = ft_strsplit_by_arr(cmd, split);	
	i = -1;
	while (args[++i])
	{
		if (ft_strequ(split, "&"))
			ft_call_cmdss(&args[i], env);
		ft_parser(args[i], get_next_spli(args[i], split), env);
	}
	ft_strrdel(args);
}

int			main(void)
{
	extern char	**environ;
	char		*str_cmds;
	int			i;

	/// Initail error 
	ft_intia_err("/dev/ttys002");
	
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
			/// Correction args : Expansions + Correct Quoting
			//ft_corr_args(&str_cmds, environ);

			///  Splite line entred with {;,&&,||,&} and Execute cmds
			//ft_parser(str_cmds, ";", &environ);
			ft_call_cmdss(&str_cmds, &environ);
			//ft_strdel(&str_cmds);
		}
	}
	//ft_strrdel(environ);
	return (0);
}

void		exit_shell(char **env)
{
	UNUSED(env);
	//ft_strrdel(env);
	enable_term();
	exit(0);
}
