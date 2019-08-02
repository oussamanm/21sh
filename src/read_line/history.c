/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/07 14:42:43 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_stock_history(char **history, char *line, int his_count)
{
	int i;

	i = 1;
	if (his_count < MAX_HISTORY)
	{
		free(history[his_count]);
		history[his_count] = ft_strdup(line);
	}
	else
	{
		free(history[0]);
		while (i < MAX_HISTORY)
		{	
			history[i - 1] = history[i];
			i++;
		}
		history[MAX_HISTORY - 1] = ft_strdup(line);
	}
}

void	ft_print_history(t_history *his, char *buf, char **s, t_cursor *pos)
{
	int num_col;
	int num_lines;

	num_col = ft_get_size_windz();
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	if (UP == CAST(buf))
	{	
		his->his_count--;
		ft_stock_history(his->history, *s, his->his_count + 1);
	}
	else
		his->his_count++;
	ft_putstr(his->history[his->his_count]);
	ft_get_end_of_line_pos(pos, his->history[his->his_count], num_col);
	num_lines = ft_get_num_of_lines(num_col, his->history[his->his_count], pos->p);
	pos->index = ft_strlen(his->history[his->his_count]);
	pos->x = pos->end[num_lines - 1];
	pos->y = num_lines - 1;
	free(*s);
	*s = ft_strdup(his->history[his->his_count]);
}
