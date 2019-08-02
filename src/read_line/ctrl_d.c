/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:14:32 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/17 17:14:33 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	ft_free_tab(char **tableau)
{
	int i;

	i = 0;
	while (tableau[i])
		free(tableau[i++]);
	free(tableau);
}

void	ft_read_line_exit(t_cursor *pos, t_history *his, t_select *select)
{
    if (pos->end)
        free(pos->end);
    if (pos->cmd)
        free(pos->cmd);
    if (select->save)
        free(select->save);
    if (his->history)
        ft_free_tab(his->history);
}

char	*ft_ctrl_d(t_cursor *pos, t_history *his, t_select *select, char *s)
{
    char	*new;
	int		len;

    if (!ft_strcmp(s, ""))
    {
        ft_read_line_exit(pos, his, select);
		exit(0);
    }
	len = ft_strlen(s);
	pos->num_col = ft_get_size_windz();
	if (pos->index < len && pos->index >= 0)
	{
        tputs(tgetstr("cd", NULL), 0, my_outc);
		new = ft_memalloc(sizeof(char) * len);
		ft_strncpy(new, s, pos->index);
		ft_strcpy(new + pos->index, s + pos->index + 1);
		ft_putstr_term(pos->num_col, new + pos->index, pos);
		pos->num_lines = ft_get_num_of_lines(pos->num_col, new, pos->p);
		ft_get_end_of_line_pos(pos, new, pos->num_col);
		ft_set_last_position(*pos, pos->num_lines);
	}
	else
		return (s);
	free(s);
	return (new);
}
