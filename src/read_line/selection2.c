/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 21:56:04 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/04/24 21:56:07 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_pos_of_left_select(t_cursor *pos, int *up)
{
	if (pos->x == 0 && pos->index != 0)
	{
		*up = 1;
		pos->y--;
		pos->x = pos->end[pos->y];
	}
	else if (pos->index != 0)
		pos->x--;
}

void	ft_first_left_select(t_cursor *pos, t_select *select, char *s)
{
	if (pos->index != 0)
	{
		select->start = pos->index;
		select->end = pos->index;
		ft_print_with_reverse_mode(s , select->start, select->end, pos);
	}
	else
		ft_putstr_term(pos->num_col, s, pos);
}

void	ft_remove_last_select_left(t_cursor *pos, t_select *select, char *s, int up)
{
	int len;

	len = ft_strlen(s);
	select->end--;
	if (up)
		ft_movecur_up_and_right(1, pos->num_col);
	else
		tputs(tgetstr("le", NULL), 0, my_outc);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr_term(pos->num_col, s + select->end + 1, pos);
	if ((select->start == select->end + 1) &&
		(pos->index < len - 1 && pos->index > select->end + 1))
	{
		select->start = -1;
		select->end = -1;
	}
}

void	ft_select_left_one(t_cursor *pos, t_select *select, char *s)
{
	if (select->end != 0)
		select->end--;
	ft_print_with_reverse_mode(s ,select->end, select->start, pos);
}

void	ft_left_selection(char *s, t_cursor *pos, t_select *select)
{
	int len;
	int up;

	up = 0;
	len = ft_strlen(s);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, s, pos->p);
	if (pos->index <= len && pos->index >= 0)
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_pos_of_left_select(pos, &up);
		if (select->end == -1 && select->start == -1)
			ft_first_left_select(pos, select, s);
		else if ((select->start < select->end) || ((select->start == select->end)
			&& (pos->index < len - 1 && pos->index >= select->end)))	
			ft_remove_last_select_left(pos, select, s, up);
		else if ((select->start > select->end) || ((select->start == select->end)
			&& (pos->index == len - 1 || pos->index < select->end)))
			ft_select_left_one(pos, select, s);
		ft_set_last_position(*pos, pos->num_lines);
		if (pos->index != 0)
			pos->index--;
	}
}