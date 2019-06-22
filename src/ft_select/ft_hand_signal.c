/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hand_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 19:46:18 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 23:42:24 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_sig_ws(int argc)
{
	UNUSED(argc);
	call_sig(SIGWINCH * -1, NULL, NULL, NULL);
}

void	ft_sig_int(void)
{
	call_sig(SIGINT * -1, NULL, NULL, NULL);
}

void	ft_sig_sussp(int argc)
{
	UNUSED(argc);
	call_sig(SIGTSTP * -1, NULL, NULL, NULL);
}

void	ft_sig_cont(int argc)
{
	UNUSED(argc);
	signal(SIGTSTP, ft_sig_sussp);
	call_sig(SIGCONT * -1, NULL, NULL, NULL);
}

void	ft_sig_quit(void)
{
	call_sig(SIGQUIT * -1, NULL, NULL, NULL);
}
