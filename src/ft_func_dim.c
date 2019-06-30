/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_dim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 22:35:59 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 21:59:06 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_move_cur(char capa[2], int c, int r)
{
	char *temp;

	temp = tgetstr(capa, NULL);
	tputs(tgoto(temp, c, r), 1, &ft_putchar_err);
}

void		ft_capa_str(char capa[2])
{
	char	*temp;

	temp = tgetstr(capa, NULL);
	tputs(temp, 1, &ft_putchar_err);
}

int			ft_putchar_err(int c)
{
	write(2, &c, 1);
	return (1);
}

t_dimen	*ft_init_dim()
{
	t_dimen *st_dimen;

	st_dimen = (t_dimen *)malloc(sizeof(t_dimen));
	st_dimen->index_c = 3;
	st_dimen->nbr_row = 0;
	st_dimen->max_cln = NULL;
	if (ioctl(0, TIOCGWINSZ, &(st_dimen->st_size)) == -1)
		ft_putstr("Error to get size of terminal !!!\n");
	st_dimen->nbr_cln = st_dimen->st_size.ws_col;
	st_dimen->nbr_row = st_dimen->st_size.ws_row;
	st_dimen->len_arg = 0;
	return (st_dimen);
}