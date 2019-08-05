/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 21:01:27 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 21:01:28 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

///*** PARSER : Read tokens, Apply redirection, Update args  *****////

static void     ft_read_tokens(t_pipes *st_pipes, t_tokens *st_tokens)
{
	t_redir		*st_redir;
	t_redir		*head;

	head = NULL;
	while (st_tokens != NULL)
	{
		if (st_tokens->token < 0) /// Redirection
		{
			if (head == NULL)
			{
				st_redir = ft_new_redir();
				head = st_redir;
			}
			else
			{
				st_redir->next = ft_new_redir();
				st_redir = st_redir->next;
			}
			if (CHECK_TOKEN(st_tokens->token, T_RED_OUT_S, T_RED_OUT_A, T_RED_OUT_B))	/// OUT_PUT
				ft_redi_out(st_redir, st_tokens);
			else if (CHECK_TOKEN(st_tokens->token, T_RED_IN_S, T_RED_IN_A, T_RED_IN_B))	/// IN_PUT
				ft_redi_in(st_redir, st_tokens);
			else if (CHECK_TOKEN(st_tokens->token, T_RED_APP_S, T_RED_APP_M, T_RED_APP_A))		/// APPEND
				ft_redi_app(st_redir, st_tokens);
			else if (st_tokens->token == T_RED_BOTH)									/// <>
				ft_redi_both(st_redir, st_tokens);
			else if (st_tokens->token == T_RED_HER_D)					/// HERE_DOC
				ft_redi_her(st_redir, st_tokens);
		}
		st_tokens = st_tokens->next;
	}
	st_pipes->st_redir = head;
}

static int		ft_apply_redi(t_pipes *st_pipes)
{
	t_redir *lst_redi;
	
	if (st_pipes == NULL)
		return (REDI_KO);
	lst_redi = st_pipes->st_redir;
	while (lst_redi != NULL)
	{
		if (lst_redi->type_red == 4)
			ft_apply_hered(lst_redi);
		if (lst_redi->fd_close != -1)
			close(lst_redi->fd_close);
		if (lst_redi->fd_red != -1 && lst_redi->fd_des != -1)
		{
			if (lst_redi->fd_des == -2)
				lst_redi->fd_des = ft_open_file(lst_redi->fd_file, lst_redi->type_red);
			if (lst_redi->fd_des == -1 || !ft_exist_fd(lst_redi->fd_des))
				return (REDI_KO);
			if (dup2(lst_redi->fd_des , lst_redi->fd_red) == -1)
				return (0 && ft_putendl_fd("Error in dub", 2));
		}
		if (lst_redi->fd_err != -1 && lst_redi->fd_des != -1)
		{
			if (dup2(lst_redi->fd_des, lst_redi->fd_err) == -1)
				return (0 && ft_putendl_fd("Error in dub", 2));
		}
		lst_redi = lst_redi->next;
	}
	return (REDI_OK);
}

void		ft_update_tokens(t_tokens *st_tokens)
{
	char *temp;
	t_tokens *st_temp;

	st_temp = st_tokens;
	while (st_temp)
	{
		if (st_temp->token == 1)
		{
			temp = ft_strsub(st_temp->value , 1, ft_strlen(st_temp->value) - 2);
			ft_strdel(&(st_temp->value));
			st_temp->value = temp;
		}
		st_temp = st_temp->next;
	}
}

static void     ft_update_args(t_pipes *st_pipes)
{
	int count;
	int	i;
	t_tokens	*st_temp;

	count = 0;
	i = 0;
	st_temp = st_pipes->st_tokens;
	while (st_temp != NULL && st_temp->value != NULL)
	{
		if (!(st_temp->token < 0 || st_temp->is_arg == 1))
			count++;
		st_temp = st_temp->next;
	}
	st_temp = st_pipes->st_tokens;
	ft_strrdel(st_pipes->args);
	st_pipes->args = ft_strr_new(count);
	while (st_temp != NULL && st_temp->value != NULL)
	{
		if (!(st_temp->token < 0 || st_temp->is_arg == 1))
			(st_pipes->args)[i++] = ft_strdup(st_temp->value);
		st_temp = st_temp->next;
	}
	(st_pipes->args)[i] = NULL;
}

int             ft_parse_cmd(t_pipes *st_pipes)
{
	/// Remove quotes from tokens
	ft_update_tokens(st_pipes->st_tokens);

	// Read Tokens and fill Redirection of node cmd
	ft_read_tokens(st_pipes, st_pipes->st_tokens);
	/*
		t_redir *temp;
		temp = st_pipes->st_redir;
		while (temp)
		{
			dprintf(fd_err,"----TYEP REDIRECTION = %d\n",temp->type_red);
			dprintf(fd_err,"\tfd_red = %d\n",temp->fd_red);
			dprintf(fd_err,"\tfd_des = %d\n",temp->fd_des);
			dprintf(fd_err,"\tfd_err = %d\n",temp->fd_err);
			dprintf(fd_err,"\tfd_close = %d\n",temp->fd_close);
			dprintf(fd_err,"\tfd_file = %s\n",temp->fd_file);
			temp = temp->next;
		}
	*/
	// Apply Redirection
	if (ft_apply_redi(st_pipes) == REDI_KO)
		return (PARSE_KO);

	// Remove nodes redirection and update args
	ft_update_args(st_pipes);
	return (PARSE_OK);
}