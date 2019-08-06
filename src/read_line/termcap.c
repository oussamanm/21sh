/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:19:50 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/04/05 17:19:51 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

int		my_outc(int c)
{
	ft_putchar(c);
	return (1);
}

int		ft_set_to_default(void)
{
	if (tcsetattr(0, TCSANOW, &pos1.term) == ERR)
		return (-1);
	return (1);
}

int		ft_set_termcap(void)
{
	struct termios term;

	if (tgetent(NULL, getenv("TERM")) != 1)
		return (-1);
	if (tcgetattr(0, &term) == ERR)
		return (-1);
	if (tcgetattr(0, &pos1.term) == ERR)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, &term) == ERR)
		return (-1);
	return (0);
}
