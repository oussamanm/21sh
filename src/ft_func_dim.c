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
	write(1, &c, 1);
	return (1);
}
