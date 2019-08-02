/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_by_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 19:41:24 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/06/11 19:41:31 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_next_line(t_cursor *pos, char *s, int num_col)
{
	if (s[pos->index] == '\n')
    {
        pos->x = 0;
        pos->y++;
        pos->index++;
    }
    while (s[pos->index] && s[pos->index] != '\n')
    {
        if (pos->x == num_col - 1)
        {
            pos->x = 0;
            pos->y++;
        }
        else
            pos->x++;
        pos->index++;
    }

}

void	ft_last_line(t_cursor *pos, char *s)
{
	if (pos->x == 0 && s[pos->index - 1] == '\n')
	{
		pos->y--;
		pos->x = pos->end[pos->y];
		pos->index--;
	}
	while (pos->index > 0)
	{
		if (pos->x == 0 && s[pos->index - 1] != '\n')
		{
			pos->y--;
			pos->x = pos->end[pos->y];
		}
		else if (pos->x == 0 && s[pos->index - 1] == '\n')
			break ;
		else
			pos->x--;
		pos->index--;
	}
}

void	ft_move_by_lines(t_cursor *pos, char *s, char *buf)
{
    int num_col;
    int num_lines;

    num_col = ft_get_size_windz();
    num_lines = ft_get_num_of_lines(num_col, s, pos->p);
    if (ALT_DO == CAST(buf))
    {
        tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
        ft_next_line(pos, s, num_col);
        ft_set_last_position(*pos, num_lines);
    }
	if (ALT_UP == CAST(buf))
	{
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(num_col, s + pos->index, pos);
		ft_last_line(pos, s);
		ft_set_last_position(*pos, num_lines);
	}
}