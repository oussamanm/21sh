/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/07 14:42:43 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_remove_selections(t_cursor *pos, t_select *select, char *s)
{
	int		num_col;
	int		num_lines;

	num_col = ft_get_size_windz();
	num_lines = ft_get_num_of_lines(num_col, s, pos->p);
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr(s);
	select->start = -1;
	select->end = -1;
	ft_set_last_position(*pos, num_lines);
}

void	ft_win_change(int sig)
{
    sig = 0;
	if (pos1.cmd)
	{
		pos1.num_col = ft_get_size_windz();
		tputs(tgetstr("cl", NULL), 0, my_outc);
		ft_putstr("\033[0;32m21sh $>\033[0m ");
		ft_putstr(pos1.cmd);
		ft_get_end_of_line_pos(&pos1, pos1.cmd, pos1.num_col);
		pos1.num_lines = ft_get_num_of_lines(pos1.num_col, pos1.cmd, pos1.p);
		pos1.index = ft_strlen(pos1.cmd);
		pos1.x = pos1.end[pos1.num_lines - 1];
		pos1.y = pos1.num_lines - 1;
	}
}

void	ft_putstr_term(int num_col, char *s, t_cursor *pos)
{
	int i;
	int x;

	i = 0;
	x = pos->x;
	while (s[i])
	{
		ft_putchar(s[i]);
		if (x == num_col - 1 || s[i] == '\n')
		{
			if (x == num_col - 1 && s[i] != '\n')
				tputs(tgetstr("do", NULL), 0, my_outc);
			x = 0;
		}
		else
			x++;
		i++;
	}
}

char	*ft_putline(char c, char *s, t_cursor *pos)
{
	char *new;
	int	num_col;
	char buff[2];

	num_col = ft_get_size_windz();
	buff[0] = c;
	buff[1] = '\0';
	ft_putchar(buff[0]);
	if (pos->x == num_col - 1 || c == '\n')
	{
		pos->end[pos->y] = pos->x;
		if (c != '\n')
			tputs(tgetstr("do", NULL), 0, my_outc);
		pos->x = 0;
		pos->y++;
	}
	else
	{
		pos->x++;
		pos->end[pos->y] = pos->x;
	}
	pos->index++;
	new = ft_strjoin(s, buff);
	free(s);
	return (new);
}

void	ft_print_touch_and_join(t_cursor *pos, char *buf, char **s)
{
	int i;

	i = 0;
	while ((ft_isprint(buf[i]) || buf[i] =='\n') && i < 6)
		*s = ft_putline(buf[i++], *s, pos);
}
