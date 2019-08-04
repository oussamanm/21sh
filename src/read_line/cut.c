/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 00:57:34 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/08/04 00:57:35 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_cut_complete(t_cursor *pos, t_select *select, char **s, int len)
{
	int len_sa;

	len_sa = ft_strlen(select->save);
	while (len_sa--)
	{
		if (pos->x == 0)
		{	
			pos->y--;
			pos->x = pos->end[pos->y];
			ft_movecur_up_and_right(1, pos->x);
			pos->index--;
			continue ;
		}
		tputs(tgetstr("le", NULL), 0, my_outc);
		pos->x--;
		pos->index--;
	}
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_memmove(*s + pos->index, *s + select->end + 1, len);
	ft_putstr_term(pos->num_col, *s + pos->index, pos);
	ft_get_end_of_line_pos(pos, *s, pos->num_col);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
	ft_set_last_position(*pos, pos->num_lines);
}

void	ft_cut(t_cursor *pos, t_select *select, char **s)
{
	int len;

	len = ft_strlen(*s);
	ft_get_save(*s, select);
	if (select->start >= select->end && (pos->index < select->end || pos->index == 0))
	{
		if (pos->index == 0)
			ft_memmove(*s + pos->index, *s + select->start + 1, len);
		else
			ft_memmove(*s + pos->index + 1, *s + select->start + 1, len);
		if (pos->x == pos->end[pos->y])
			tputs(tgetstr("do", NULL), 0, my_outc);
		else if (pos->index != 0)
			tputs(tgetstr("nd", NULL), 0, my_outc);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		if (pos->index == 0)
			ft_putstr(*s + pos->index);
		else
			ft_putstr(*s + pos->index + 1);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
		ft_get_end_of_line_pos(pos, *s, pos->num_col);
		ft_set_last_position(*pos, pos->num_lines);
	}
	else
		ft_cut_complete(pos, select, s, len);
}
