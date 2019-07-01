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

void		ft_shift_cur(t_dimen *st_dimen)
{
	int i_c;
	int i_r;
	int bl_nega;

	bl_nega = 0;
	i_c = st_dimen->st_parg->c - st_dimen->st_pcur->c;
	i_r = st_dimen->st_parg->r - st_dimen->st_pcur->r;
	// Column
	if (i_c < 0 && (bl_nega = 1))
		i_c *= -1;
	dprintf(fd_err,"\n************ Start Clacule **********\ni_c = %d in bl_nega = %d \n",i_c,bl_nega);
	while (i_c-- != 0)
		(bl_nega == 1) ? ft_capa_str("le") : ft_capa_str("nd");
	// Row
	bl_nega = 0;
	if (i_r < 0 && (bl_nega = 1))
		i_r *= -1;
	while (i_r-- != 0)
		(bl_nega == 1) ? ft_capa_str("do") : ft_capa_str("up");
	dprintf(fd_err,"************ End **********\ni_r = %d in bl_nega = %d \n",i_r,bl_nega);	
}

int		ft_correc_cur(t_dimen *st_dimen)
{
	int curr_row;
	int len_arg;
	int rtn;

	rtn = 0;
	len_arg = (st_dimen->len_arg + 3);
	curr_row = ((st_dimen->st_pcur->r + 1) * st_dimen->nbr_cln);
	if (st_dimen->index_c < 3 || ((st_dimen->st_pcur->c < 3) && (st_dimen->st_pcur->r == 0)))
	{
		st_dimen->index_c = 3;
		st_dimen->st_pcur->c = 3;
		st_dimen->st_parg->c = 3;
		rtn++;
	}
	else if (st_dimen->index_c > len_arg || st_dimen->st_pcur->c > len_arg)
	{
		st_dimen->index_c = len_arg;
		st_dimen->st_pcur->c = len_arg;
		st_dimen->st_parg->c = len_arg;
		rtn++;
	}
	return (rtn);
}

void		ft_clear_cur(t_posit *st_posit)
{
	st_posit->r = 0;
	st_posit->c = 0;
}

void		ft_crea_cur(t_dimen *st_dimen, int bl_type, int nbr)
{
	t_posit *st_ptr;
	int c;

	c = 0;
	st_ptr = (bl_type == 0) ? st_dimen->st_pcur : st_dimen->st_parg;
	dprintf(fd_err,"Before in bl_type =%d : c = %d and r = %d\n",bl_type,st_ptr->c,st_ptr->r);
	c = st_dimen->index_c + nbr;
	st_ptr->r = c / st_dimen->nbr_cln;
	st_ptr->c = c % st_dimen->nbr_cln;
	/*while (nbr != 0)
	{
		if ((st_ptr->c + 1) == st_dimen->nbr_cln)
		{
			st_ptr->r++;
			st_ptr->c = 0;
		}
		else
			st_ptr->c++;
		nbr--;
	}*/
	dprintf(fd_err,"After in bl_type =%d :c = %d and st_ptr->c = %d and st_ptr->r = %d\n\n",bl_type,c,st_ptr->c,st_ptr->r);
}

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