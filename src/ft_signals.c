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
	if (!g_sign)
		ft_putstr("\n\033[0;32m21sh $>\033[0m ");
	else
		ft_putchar('\n');
}

void ft_call_signal()
{
	signal(SIGINT, ft_catch_signal);
    signal(SIGWINCH, ft_win_change);
}
