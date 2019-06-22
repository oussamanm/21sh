/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:17:04 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/16 23:22:31 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_restor_attr(int fd, struct termios *st_savedattr)
{
	ft_capa_str("te");
	if (tcsetattr(fd, TCSANOW, st_savedattr) == -1)
		ft_putstr("Error: in Reste default tr\n");
	ft_capa_str("ve");
}

int			ft_creat_interf(struct termios *st_savedattr)
{
	struct termios	st_term;
	int				fd;

	if ((fd = open(ttyname(0), O_RDWR)) < 0)
		ft_err_exit("Device file not found !\n");
	if (isatty(fd) != 1)
		ft_err_exit("FD doesn't refers to a valid terminal type device \n");
	if (tcgetattr(fd, st_savedattr) != 0)
		ft_err_exit("Error tcgetattr \n");
	if (tgetent(NULL, getenv("TERM")) != 1)
		ft_err_exit("Error tgetent ,may variable TERM not valid! \n");
	ft_capa_str("vi");
	if (tcgetattr(fd, &st_term) != 0)
		ft_putstr("Error in tcgetattr() \n");
	st_term.c_lflag &= ~(ICANON | ECHO);
	st_term.c_cc[VMIN] = 1;
	st_term.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSANOW, &st_term) != 0)
		ft_putstr("Error in tcsetattr() \n");
	return (fd);
}

static int	ft_action(int i, t_args **st_list, t_dimen *dim)
{
	if (i == TR_ESC)
		return (-1);
	else if (i == TR_ENT)
		return (2);
	else if (i == TR_SPC)
		return (ft_bt_select(*st_list, dim));
	else if (i == 2117294875 || i == 127)
		return (ft_bt_del(st_list));
	else if (i == TR_UP)
		return (ft_bt_up(*st_list, dim));
	else if (i == TR_DW)
		return (ft_bt_dw(*st_list, dim));
	else if (i == TR_RG)
		return (ft_bt_rg(*st_list, dim));
	else if (i == TR_LF)
		return (ft_bt_lf(*st_list, dim));
	return (0);
}

static int	ft_read(int fd, t_args **st_list, t_dimen **dim)
{
	int temp;
	int rtn;

	while (1)
	{
		temp = 0;
		if (read(fd, &temp, 4) < 0)
			ft_putstr("Error Read !\n");
		if (temp == 0)
			continue ;
		rtn = ft_action(temp, st_list, *dim);
		if (rtn == -1)
			return (-1);
		else if (rtn == 3)
		{
			(*dim != NULL) ? free((*dim)->max_cln) : NULL;
			(*dim != NULL) ? free(*dim) : NULL;
			*dim = ft_fill_dim(fd, *st_list);
			ft_upd_interf(*st_list, *dim);
		}
		if (rtn == 2)
			return (1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	int				fd;
	struct termios	st_savedattr;
	t_args			*st_list;
	t_dimen			*dim;

	if (argc < 2)
		return (0);
	fd = ft_creat_interf(&st_savedattr);
	st_list = ft_fill_list(argc - 1, &argv[1]);
	dim = ft_fill_dim(fd, st_list);
	call_sig(fd, st_list, &dim, &st_savedattr);
	signal(SIGWINCH, ft_sig_ws);
	signal(SIGINT, ft_sig_int);
	signal(SIGTSTP, ft_sig_sussp);
	signal(SIGCONT, ft_sig_cont);
	signal(SIGQUIT, ft_sig_quit);
	ft_upd_interf(st_list, dim);
	argc = ft_read(fd, &st_list, &dim);
	ft_restor_attr(fd, &st_savedattr);
	if (argc == 1)
		ft_seleted_itm(st_list);
	(dim != NULL && dim->max_cln != NULL) ? free(dim->max_cln) : NULL;
	(dim != NULL) ? free(dim) : NULL;
	ft_lst_del(&st_list);
	return (0);
}
