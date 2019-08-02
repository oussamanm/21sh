/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 21:21:36 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/05/10 21:21:38 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void    ft_get_save(char *s, t_select *select)
{
    int start;
    int end;

    if (select->end >= select->start)
    {
        start = select->start;
        end = select->end;
    }
    else
    {
        start = select->end;
        end = select->start;
    }
    select->save = ft_strsub(s, start, end - start + 1);
}

void	ft_remove_selection(t_cursor *pos, char *s)
{
    int len;
	int x_save;

	x_save = pos->x;
	len = ft_strlen(s);
	ft_move_cursor_zero(*pos);
	tputs(tgetstr("cd", NULL), 0, my_outc);
	ft_putstr(s);
	pos->x = x_save;
	ft_set_last_position(*pos, pos->num_lines);
}

char	*ft_paste_in_str(char *s, t_select *select, int index)
{
	int	i;
	int j;
	int len;
	char *fr;

	i = 0;
	j = 0;
	len = ft_strlen(s) + ft_strlen(select->save);
	fr = ft_strnew(len + 1);
	while (i < index)
	{	
		fr[i] = s[i];
		i++;
	}
	while (select->save[j])
		fr[i++] = select->save[j++];
	while (i < len)
		fr[i++] = s[index++];
	fr[i] = '\0';
	free(s);
	return (fr);
}

void	ft_get_new_pos(t_cursor *pos, int len_sa)
{
	while (len_sa--)
	{
		if (pos->x == pos->end[pos->y])
		{
			pos->y++;
			pos->x = 0;
		}
		else
			pos->x++;
	}
}

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

void    ft_copy_paste(char *buf, char **s, t_cursor *pos, t_select *select)
{
    int len;
	int len_sa;

	len = ft_strlen(*s);
	pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
    if (COPY == CAST(buf) && select->start != -1 && select->end != -1)
    {
        ft_get_save(*s, select);
        select->start = -1;
        select->end = -1;
        ft_remove_selection(pos, *s);
    }
	if (CUT == CAST(buf) && select->start != -1 && select->end != -1)
		ft_cut(pos, select, s);
	if (PASTE == CAST(buf) && select->save)
	{
		len_sa = ft_strlen(select->save);
		*s = ft_paste_in_str(*s, select, pos->index);
		tputs(tgetstr("cd", NULL), 0, my_outc);
		ft_putstr_term(pos->num_col, *s + pos->index, pos);
		ft_get_end_of_line_pos(pos, *s, pos->num_col);
		pos->index += len_sa;
		ft_get_new_pos(pos, len_sa);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, *s, pos->p);
		ft_set_last_position(*pos, pos->num_lines);
	}
}