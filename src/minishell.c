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
#include "read_line.h"

/*
** Initiale terminle attr , fill struct info and call function Read
*/

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
	if (str_cmds == NULL)
		return (1);
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
	t_history	his;
	t_select	select;

	/// Initail error 
	ft_intia_err("/dev/ttys001");
	select.start = -1;
	select.end = -1;
	select.save = NULL;
	his.history = ft_alloc_tab();
	his.his_count = 0;

	///Initial interface : tgetent
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in seting Temcap");

	///Call functions signal
	ft_call_signal();

	/// Duplicate environ
	environ = ft_strr_dup(environ, ft_strrlen(environ));
	his.path = ft_get_vrb("PATH", environ);

	while (1337)
	{
		ft_putstr("\033[0;32m21sh $>\033[0m ");
		// fill str_arg with command Entred And print prompt
		if ((str_cmds = ft_read_line(&his, &select, 8)) != NULL)
		{
			ft_stock_history(his.history, str_cmds, his.his_count);
			if (his.his_count < MAX_HISTORY)
				his.his_count++;

			/// Check all error ; | redir 
			if (ft_parse_error(str_cmds))
			{
				/// print prompt
				ft_strdel(&str_cmds);
				continue ;
			}
			/// Correction args : Expansions + Correct Quoting
			str_cmds = ft_corr_args(str_cmds, environ);
			
			///  Splite line entred with {;,&&,||,&} and Execute cmds
			//ft_parser(str_cmds, ";", &environ);
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
	exit(0);
}
