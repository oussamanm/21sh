/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:14:59 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/15 22:42:16 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_intia_err(char *tty)
{
	int fd_err;

	fd_err = 0;
	if ((fd_err = open(tty, O_RDWR)) < 0)
		ft_putstr("Error in Open func with name of tty!\n");
}

void		ft_err_exit(char *str)
{
	ft_putstr(str);
	exit(0);
}

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
