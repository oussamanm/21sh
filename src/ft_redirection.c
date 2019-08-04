/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 20:44:28 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 20:44:30 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "read_line.h"

///*** Redirection *****////

t_redir		*ft_new_redir()
{
	t_redir	*st_redir;

	st_redir = (t_redir *)malloc(sizeof(t_redir));
	st_redir->next = NULL;
	return (st_redir);
}

void		ft_init_redi(t_redir *st_redir, int type_red)
{
	if (st_redir == NULL)
		return ;
	st_redir->type_red = type_red;
	///Right redirection
	if (type_red == 1)
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = -1;
		st_redir->fd_des = -1;
		st_redir->fd_close = -1;
	}
	else if (type_red == 0)
	{
		st_redir->fd_red = 0;
		st_redir->fd_des = -1;
		st_redir->fd_err = -1;
		st_redir->fd_close = -1;
	}
	else if (type_red == 2)
	{
		st_redir->fd_red = 1;
		st_redir->fd_des = -1;
		st_redir->fd_err = -1;
		st_redir->fd_close = -1;
	}
	else if (type_red == 3)
	{
		st_redir->fd_red = 0;
		st_redir->fd_des = -1;
		st_redir->fd_err = -1;
		st_redir->fd_close = -1;
	}
	else if (type_red == 4)
	{
		st_redir->fd_red = 0;
		st_redir->fd_des = -1;
		st_redir->fd_err = -1;
		st_redir->fd_close = -1;
	}
	st_redir->fd_file = NULL;
}

/* error open function
	INPUT
	wc: stdin: read: Is a directory
	bash: asd: No such file or directory
	bash: ttt: Permission denied
	OUTPUT
	bash :ggg : Is a directory
	bash: ttt: Permission denied
*/

void	ft_apply_hered(t_redir *st_redi)
{
	int fds[2];

	if (st_redi == NULL)
		return ;
	if (pipe(fds) == -1)
		ft_putendl_fd("Error in pipe line of here_doc", 2);
	write(fds[1], st_redi->fd_file, ft_strlen(st_redi->fd_file));
	close(fds[1]);
	st_redi->fd_red = 0;
	st_redi->fd_des = fds[0];
}

void	ft_redi_out(t_redir *st_redir, t_tokens *st_tokens)
{
	/// Initiale Vrb redirection
	ft_init_redi(st_redir, 1);
	if (st_tokens->token == T_RED_OUT_S) // 7>file
	{
		if (st_tokens->prev && st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_OUT_A) /// >& || &>
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		if ((st_tokens->value)[1] == '&' && ft_isalldigit(st_tokens->next->value))
		{
			st_redir->fd_des = ft_atoi(st_tokens->next->value);
			st_tokens->next->is_arg = 1;
		}
		else // &> . >&FILE
		{
			st_redir->fd_red = 1;
			st_redir->fd_err = 2;
			st_redir->fd_des = -2;
			st_redir->fd_file = st_tokens->next->value;
			st_tokens->next->is_arg = 1;
		}
	}
	else if (st_tokens->token == T_RED_OUT_B) // >&-
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_close = ft_atoi(st_tokens->prev->value);
		else
			st_redir->fd_close = 1;
	}
}

void	ft_redi_in(t_redir *st_redir, t_tokens *st_tokens)
{
	/// Initiale Vrb redirection
	ft_init_redi(st_redir, 0);

	if (st_tokens->token == T_RED_IN_S)
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_IN_A) /// [n1]<& n2
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = ft_atoi(st_tokens->next->value); // next must be a number
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_IN_B) /// <&-
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_close = ft_atoi(st_tokens->prev->value);
	}
}

void	ft_redi_app(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 2);
	if (st_tokens->token == T_RED_APP_S)
	{
		if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value) && (st_tokens->prev->is_arg = 1))
			st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
		st_tokens->next->is_arg = 1;
	}
	else if (st_tokens->token == T_RED_APP_A)
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = 2;
		if (st_tokens->next && st_tokens->next->value && ft_isallalphanum(st_tokens->next->value))
		{
			st_redir->fd_des = -2;
			st_redir->fd_file = st_tokens->next->value;
			st_tokens->next->is_arg = 1;
		}
	}
}

void	ft_redi_both(t_redir *st_redir, t_tokens *st_tokens)
{
	ft_init_redi(st_redir, 3);
	if (st_tokens->prev->indx == st_tokens->indx && ft_isalldigit(st_tokens->prev->value))
	{
		st_tokens->prev->is_arg = 1;
		st_redir->fd_red = ft_atoi(st_tokens->prev->value);
	}
	st_redir->fd_des = -2;
	st_redir->fd_file = st_tokens->next->value;
	st_tokens->next->is_arg = 1;
}

void	ft_redi_her(t_redir *st_redir, t_tokens *st_tokens)
{
	char *content;

	/// add error of here doc syntax
	ft_init_redi(st_redir, 4);
	if (st_tokens->prev != NULL && st_tokens->prev->indx == st_tokens->indx && ft_isallprint(st_tokens->prev->value))
	{
		st_redir->fd_red = ft_atoi(st_tokens->prev->value);
		st_tokens->prev->is_arg = 1;
	}
	if (st_tokens->next != NULL && st_tokens->next->value && ft_isallprint(st_tokens->next->value))
	{
		st_tokens->next->is_arg = 1;
		content = ft_read_heredoc(st_tokens->next->value);
		ft_strdel(&(st_tokens->next->value));
		st_tokens->next->value = content;
		st_redir->fd_file = ft_strdup(content);
		st_redir->fd_des = -2;
	}
}

int		ft_error_redir(t_tokens *st_tokens)
{
	while (st_tokens != NULL)
	{
		if (st_tokens->token == -124 && st_tokens->next && st_tokens->next->token == T_TXT)
			if (st_tokens->next->indx != st_tokens->indx && st_tokens->next->next && st_tokens->next->next->token < 0)
				return (ft_putendl_fd("syntax error near unexpected token 'st_tokens->next->token'", 2));
		/// >>> || <<<
		if (st_tokens->token < -169)
			return (ft_putendl_fd("syntax error near unexpected token ", 2));
		/// & after redir
		if (st_tokens->token < 0 && ft_check_char(st_tokens->value, ERRO_IN_AND))
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		/// error token redi || null after Redirection
		if (st_tokens->token < 0 && (st_tokens->next == NULL || st_tokens->next->token < 0) && st_tokens->token != -145 && st_tokens->token != -143) /// check arg after redi !(execpt >&- , <&-)
			return (ft_putendl_fd("syntax error near unexpected token `last token'", 2));
		/// error ><
		if (st_tokens->token <= -122 && ft_strncmp(st_tokens->value, "><", 2) == 0)
			return (ft_putendl_fd("syntax error near unexpected token `<'", 2));
		/// error nbr != 1 before >&file
		if (st_tokens->token == T_RED_OUT_A && st_tokens->next  && !ft_isalldigit(st_tokens->next->value) && P_TK && P_TK->indx == st_tokens->indx
			&& ft_isalldigit(P_TK->value) && ft_atoi(P_TK->value) != 1)
			return (ft_putendl_fd("ambiguous redirect", 2));
		/// &... after redir
		if ((st_tokens->token == T_RED_OUT_A || st_tokens->token == T_RED_HER_D) && st_tokens->next && st_tokens->next->value && st_tokens->next->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		st_tokens = st_tokens->next;
	}
	return (0);
}
