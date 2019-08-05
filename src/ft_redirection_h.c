/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_h.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 17:37:00 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/05 17:37:01 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

///*** Helper Function for Redirection *****////


///*** New list redirection ***///
t_redir		*ft_new_redir()
{
	t_redir	*st_redir;

	st_redir = (t_redir *)malloc(sizeof(t_redir));
	st_redir->next = NULL;
	return (st_redir);
}

///*** Initiale vrb of rediretion ***///
void		ft_init_redi(t_redir *st_redir, int type_red)
{
	if (st_redir == NULL)
		return ;
	st_redir->type_red = type_red;
	st_redir->fd_des = -1;
	st_redir->fd_err = -1;
	st_redir->fd_close = -1;
	if (type_red == 1)		// >
		st_redir->fd_red = 1;
	else if (type_red == 0) // <
		st_redir->fd_red = 0;
	else if (type_red == 2) // >>
		st_redir->fd_red = 1;
	else if (type_red == 3) // <>
		st_redir->fd_red = 0;
	else if (type_red == 4) // <<
		st_redir->fd_red = 0;
	st_redir->fd_file = NULL;
}

///*** helper function for ft_redi_out (>& || &>) ***///
void	ft_redi_out_h(t_redir *st_redir, t_tokens *st_tokens)
{
	if (PREV && PREV->indx == st_tokens->indx &&
		ft_isalldigit(PREV->value) && (PREV->is_arg = 1))
		st_redir->fd_red = ft_atoi(PREV->value);
	if ((st_tokens->value)[1] == '&' && ft_isalldigit(st_tokens->next->value))
		st_redir->fd_des = ft_atoi(st_tokens->next->value);
	else // &> . >&FILE
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = 2;
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
	}
	st_tokens->next->is_arg = 1;
}

///*** Apply redirection her_doc ***///
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

///*** Check Error syntax of redirection
int		ft_error_redir(t_tokens *st_tokens)
{
	while (st_tokens != NULL)
	{
		if (st_tokens->token == T_RED_OUT_S && st_tokens->next && st_tokens->next->token == T_TXT && st_tokens->next->value && st_tokens->next->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
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
		if (st_tokens->token == T_RED_OUT_A && st_tokens->next  && !ft_isalldigit(st_tokens->next->value) && PREV && PREV->indx == st_tokens->indx
			&& ft_isalldigit(PREV->value) && ft_atoi(PREV->value) != 1)
			return (ft_putendl_fd("ambiguous redirect", 2));
		/// &... after redir
		if ((st_tokens->token == T_RED_OUT_A || st_tokens->token == T_RED_HER_D) && st_tokens->next && st_tokens->next->value && st_tokens->next->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		st_tokens = st_tokens->next;
	}
	return (0);
}
