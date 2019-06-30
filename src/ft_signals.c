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

static void	ft_handler_ctlc()
{
	ft_putstr("\n$> ");
}

static void	ft_handler_quit()
{
	ft_putstr("exit\n");
    ft_init_signal(SIGQUIT, NULL);
	exit(0);
}

static void ft_call_signal()
{
	signal(SIGINT, ft_handler_ctlc);
	signal(SIGQUIT, ft_handler_quit);
}

void    ft_apply_handler(int sig, t_termios *st_saveattr)
{
    if (sig == SIGQUIT)
        ft_restor_attr(0, st_saveattr);
}

/// Initial Signals : (sig = 0)->initial pointer (else)->apply handler
void    ft_init_signal(int sig, t_termios *st_saveattr)
{
    static t_termios *st_ptrattr;

    if (sig == 0)
    {
        ft_call_signal();
        st_ptrattr = st_saveattr;
    }
    else
    {
        ft_apply_handler(sig, st_ptrattr);
    }
}
