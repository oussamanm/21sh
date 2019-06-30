/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 23:03:45 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/25 23:03:49 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

///*** After print should back curs to his position
/*void		ft_corr_cur(t_dimen *st_dimen, int temp)
{
	int i_temp;
	int cur_row;

	i_temp = st_dimen->index_c + temp;
	cur_row = st_dimen->index_c / st_dimen->nbr_cln;
	dprintf(fd_err,"i_temp = %d, cur = %d and com = %d with %d\n",i_temp,st_dimen->index_c,(st_dimen->index_c / st_dimen->nbr_cln) , (i_temp / st_dimen->nbr_cln));
	if (temp == 1 && st_dimen->index_c == 20)
	{
		ft_capa_str("do");
		ft_move_cur("ch", 0, 0);
	}
	else if (temp > 1)
	{
		if (cur_row == ((i_temp - 1) / st_dimen->nbr_cln))	 /// in case of same row
		{
			dprintf(fd_err,"in cond1\n");
			ft_move_cur("LE", 0, temp);
		}
		else if (cur_row < (i_temp / st_dimen->nbr_cln)) /// in case of row changed
		{
			dprintf(fd_err,"in cond2\n");
			ft_capa_str("up");
			ft_move_cur("ch", 0, (st_dimen->index_c % st_dimen->nbr_cln));
		}
		else if (st_dimen->index_c == (st_dimen->nbr_cln * cur_row)) /// in case of cur in last cln
		{
			dprintf(fd_err,"in cond4\n");
			ft_move_cur("ch", 0, 0);
			// should add case of i_temp is too hight
		}
	}
}*/
/*
int		ft_index_cur(t_dimen *st_dimen, int *r, int *c)
{
	int rtn;

	rtn = 0;
	if (st_dimen == NULL)
		return (0);
	if (st_dimen->index_c < 3 && ++rtn)
		st_dimen->index_c = 3;
	if (st_dimen->index_c > (st_dimen->len_arg + 3) && ++rtn)
	{
		dprintf(fd_err,"in condition > ft_index_cur");
		st_dimen->index_c = (st_dimen->len_arg + 3);
	}
	if (r != NULL)
		*r = st_dimen->index_c / st_dimen->nbr_cln;
	if (c != NULL)
		*c = st_dimen->index_c % st_dimen->nbr_cln;
	dprintf(fd_err,"r = %d and c = %d and cur = %d and nbr_cln = %d \n",*r,*c,st_dimen->index_c,st_dimen->nbr_cln);
	return (rtn);
}*/

///*** Initialize datab base of termcap & apply attr ICANON,ECHO mode
void		ft_init_interf(t_termios *st_savedattr)
{
	struct termios	st_term;
	int				fd;

	UNUSED(fd);
	/*if ((fd = open(ttyname(0), O_RDWR)) < 0)
		ft_err_exit("Device file not found !\n");
	if (isatty(fd) != 1)
		ft_err_exit("FD doesn't refers to a valid terminal type device \n");*/
	// Save old attr of terminal to restore them
	if (tcgetattr(0, st_savedattr) != 0)
		ft_err_exit("Error tcgetattr \n");
	// Initail Data Base of Termcap
	if (tgetent(NULL, getenv("TERM")) != 1)
		ft_err_exit("Error tgetent ,may variable TERM not valid! \n");
	if (tcgetattr(0, &st_term) != 0)
		ft_putstr("Error in tcgetattr() \n");
	st_term.c_lflag &= ~(ICANON | ECHO);
	st_term.c_cc[VMIN] = 1;
	st_term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &st_term) != 0)
		ft_putstr("Error in tcsetattr() \n");
}

void		ft_restor_attr(int fd, t_termios *st_savedattr)
{
	ft_capa_str("te");
	if (tcsetattr(fd, TCSANOW, st_savedattr) == -1)
		ft_putstr("Error: in Reste default tr\n");
	ft_capa_str("ve");
}