/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:36:54 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/18 12:31:36 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"


void	ft_enter(t_cursor *pos, t_select *select, char *s)
{
	if (select->start != -1 && select->end != -1)
		ft_remove_selections(pos, select, s);
	ft_putstr_term(pos->num_col, s + pos->index, pos);
	ft_putchar('\n');
}

char	*ft_read_line(t_history *his, t_select *select, int p)
{
	char	buf[6];	
	char	*s;
	char	*tmp;
	int		len;

	ft_initial(&s, p);
	ft_bzero(buf, 6);
	g_fd = fopen("/dev/ttys004", "a+");
	while ((len = read(0, buf, 6)))
	{
		fprintf(g_fd, "key = %d\n", *((int *)buf));
		if (ENTER == CAST(buf))
		{
			ft_enter(&pos1, select, s);
			break ;
		}
		else if (TAB == CAST(buf))
			s = ft_auto_completion(&pos1, his, s);
		else if (CTRL_D == CAST(buf))
			s = ft_ctrl_d(&pos1, his, select, s);
		else if (ALT_UP == CAST(buf) || ALT_DO == CAST(buf))
			ft_move_by_lines(&pos1, s, buf);
		else if (HOME == CAST(buf) || END == CAST(buf))
			ft_home_end(&pos1, s, buf);
		else if (RI_WOR == CAST(buf) || LE_WOR == CAST(buf))
			ft_move_by_word(&pos1, s, buf);
		else if (DEL == CAST(buf))
			s = ft_delcolomn(s, &pos1);
		else if ((UP == CAST(buf) && his->his_count != 0)
			|| (DO == CAST(buf) && his->history[his->his_count + 1]))
			ft_print_history(his, buf, &s, &pos1);
		else if (LE == CAST(buf) || RI == CAST(buf))
			ft_see_touch(buf, s, &pos1, select);
		else if (SEL_RI == CAST(buf) || SEL_LE == CAST(buf))
			ft_selection(s, &pos1, buf, select);
		else if (COPY == CAST(buf) || PASTE == CAST(buf) || CUT == CAST(buf))
			ft_copy_paste(buf, &s, &pos1, select);	
		else if (ft_isprint(buf[0]) && (size_t)pos1.index != ft_strlen(s))
			s = ft_line_edd(s, &pos1, buf[0]);
		else
			ft_print_touch_and_join(&pos1, buf, &s);
		if (pos1.cmd)
			free(pos1.cmd);
		pos1.cmd = ft_strdup(s);
		ft_bzero(buf, 6);
	}
	tmp = s;
	s = ft_strtrim(s);
	free(tmp);
	return (s);
}
