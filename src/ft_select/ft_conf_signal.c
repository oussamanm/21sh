/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:19:29 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 23:37:49 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	ft_sig_interr(int sig, t_args *args, t_dimen **dim,
		t_termios *attr)
{
	if (sig == (SIGINT * -1) || sig == (SIGQUIT * -1))
	{
		ft_lst_del(&args);
		ft_restor_attr(0, attr);
		exit(0);
	}
	else if (sig == (SIGTSTP * -1))
	{
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\x1A");
		ft_restor_attr(0, attr);
	}
	else if (sig == (SIGCONT * -1))
	{
		ft_creat_interf(attr);
		ft_upd_interf(args, *dim);
	}
}

void		call_sig(int argc, t_args *st_list, t_dimen **dim,
		t_termios *old_attr)
{
	static t_args		*ptr_args;
	static t_dimen		**ptr_dim;
	static t_termios	*ptr_attr;
	static int			fd;

	if (argc > 0)
	{
		ptr_args = st_list;
		ptr_dim = dim;
		fd = argc;
		ptr_attr = old_attr;
	}
	else if (argc == (SIGWINCH * -1))
	{
		(*ptr_dim != NULL) ? free((*ptr_dim)->max_cln) : NULL;
		(*ptr_dim != NULL) ? free(*ptr_dim) : NULL;
		*ptr_dim = ft_fill_dim(fd, ptr_args);
		ft_upd_interf(ptr_args, *ptr_dim);
	}
	else
		ft_sig_interr(argc, ptr_args, ptr_dim, ptr_attr);
}
