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
#include "termcap.h"

static void	ft_handler_ctlc()
{
    ft_init_signal(SIGINT, NULL);
}

static void	ft_handler_quit()
{
	ft_init_signal(SIGQUIT, NULL);
}

void ft_call_signal()
{
	signal(SIGINT, ft_handler_ctlc);
	signal(SIGQUIT, ft_handler_quit);
}

void    ft_apply_handler(int sig, struct s_termcap *info)
{
    UNUSED(info);
    if (sig == SIGINT)
        ft_putstr("\n$> ");
    if (sig == SIGQUIT)
    {
        enable_term();
	    ft_putstr("exit\n");
	    exit(0);
    }
}

/// Initial Signals : (sig = 0)->initial pointer (else)->apply handler
void    ft_init_signal(int sig, struct s_termcap *info)
{
    static struct s_termcap	*ptr;

    if (sig == 0)
    {
        ptr = info;
    }
    else
    {
        ft_apply_handler(sig, ptr);
    }
}
