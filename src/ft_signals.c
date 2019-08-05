/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:35:32 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/25 21:35:34 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "read_line.h"

void	ft_catch_signal(int signal)
{
	signal = 0;
	if (g_sign)
		ft_putchar('\n');
	else
	{
		ft_putstr_term(pos1.num_col, pos1.cmd + pos1.index, &pos1);
		ft_putstr("\n\033[0;32m21sh $>\033[0m ");
		free(pos1.end);
		if (!(pos1.end = ft_memalloc(sizeof(int) * 20)))
			return ;
		pos1.index = 0;
		pos1.p = 8;
		pos1.x = 8;
		pos1.y = 0;
		pos1.num_col = ft_get_size_windz();
		ft_strdel(&pos1.cmd);
		pos1.cmd = ft_strnew(0);
	}
}

void ft_call_signal()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_catch_signal);
    signal(SIGWINCH, ft_win_change);
}

void	ft_signal_default()
{
	signal(SIGQUIT, SIG_DFL);
}
