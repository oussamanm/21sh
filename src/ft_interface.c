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

///*** Print char
void		ft_print_char(char **arg, int temp, t_dimen *st_dimen)
{
	int i_temp;

	i_temp = 1;
	if (st_dimen->index_c == (st_dimen->len_arg + 3))
		*arg = ft_strjoir(*arg, (char [2]){temp, '\0'}, 1);
	else
		*arg = ft_add_char(*arg, st_dimen->index_c - 3, temp, 0);
	(st_dimen->index_c)++;
	(st_dimen->len_arg)++;
	ft_putchar(temp);
	if (st_dimen->index_c != (st_dimen->len_arg + 3)) /// If Curs not in last word
	{
		i_temp = ft_putstr(&(*arg)[st_dimen->index_c - 3]);
		ft_shift_cur(st_dimen, (i_temp > 1) ? (i_temp * -1) : 1, 1);
	}
	else
	{
		ft_capa_str("le");
		ft_shift_cur(st_dimen, (i_temp > 1) ? (i_temp * -1) : 1, 0);
	}
}

///*** After print should back curs to his position : if (bl == 1) -> print many char 
void		ft_shift_cur(t_dimen *st_dimen, int nbr, int bl)
{
	int i_nega;
	int curr_row;

	i_nega = (nbr < 0) ? -1 : 1;
	nbr *= (nbr < 0) ? -1 : 1;
	if (ft_correc_cur(st_dimen))
		return ;
	if (bl == 0)
	{
		if (glb == 1)
		{
			(i_nega > 0) ? ft_capa_str("nd") : ft_capa_str("le");
			return ;
		}
		curr_row = (st_dimen->index_c / st_dimen->nbr_cln);
		if (i_nega < 0 && st_dimen->index_c == (((curr_row + 1) * st_dimen->nbr_cln) - 1)) /// first cln
		{
			ft_capa_str("up");
			ft_move_cur("ch", 0, st_dimen->nbr_cln - 1);
		}
		else if (i_nega > 0 && st_dimen->index_c == (((curr_row) * st_dimen->nbr_cln))) 	/// last cln
		{
			ft_capa_str("do");
			ft_move_cur("ch", 0, 0);
		}
		else
			(i_nega > 0) ? ft_capa_str("nd") : ft_capa_str("le");
	}
	else
		ft_move_cur("LE", 0, nbr);
}

///*** Correct Cur if > len || < 3
int			ft_correc_cur(t_dimen *st_dimen)
{
	int rtn;

	rtn = 0;
	if (st_dimen->index_c < 3 && ++rtn)
		st_dimen->index_c = 3;
	else if (st_dimen->index_c > (st_dimen->len_arg + 3) && ++rtn)
		st_dimen->index_c = st_dimen->len_arg + 3;
	return (rtn);
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