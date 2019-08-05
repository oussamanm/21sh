/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 14:42:41 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/07/18 12:33:46 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char	**ft_alloc_tab(void)
{
	int		i;
	char	**tb;

	i = 0;
	if (!(tb = (char **)malloc(sizeof(char *) * MAX_HISTORY + 1)))
		return (NULL);
	while (i < MAX_HISTORY)
		tb[i++] = NULL;
	tb[i] = 0;
	return (tb);
}

int		ft_get_size_windz(void)
{
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

void	ft_init(int **d, int size)
{
	int i;

	i = 0;
	while (i < size)
		(*d)[i++] = -1;
}

void	ft_init_size_end_line(t_cursor *pos)
{
	int n;

	if (pos->num_lines > MAX_LINES)
	{
		if (pos->end)
			free(pos->end);
		n = pos->num_lines + MAX_LINES;
		if (!(pos->end = ft_memalloc(sizeof(int) * n)))
			return ;
		ft_init(&pos->end, pos->num_lines + MAX_LINES);
	}
	else
		ft_init(&pos->end, MAX_LINES);
}

/*
** - function initial all parameters of the cursor struct.
*/

void	ft_initial(int p)
{
	pos1.cmd = ft_strnew(0);
	pos1.index = 0;
	pos1.p = p;
	pos1.x = p;
	pos1.y = 0;
	pos1.num_col = ft_get_size_windz();
	if (!(pos1.end = ft_memalloc(sizeof(int) * MAX_LINES)))
		return ;
	ft_init(&pos1.end, MAX_LINES);
}
