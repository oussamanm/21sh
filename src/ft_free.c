/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:26:08 by onouaman          #+#    #+#             */
/*   Updated: 2019/07/17 19:26:09 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
