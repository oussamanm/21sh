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
	int i;
	char **tb;

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

void	ft_mmmm(int **d)
{
	int i;

	i = 0;
	while (i < 20)
		(*d)[i++] = -1;
}

void	ft_initial(char **s, int p)
{
	*s = ft_strnew(0);
	pos1.index = 0;
	pos1.p = p;
	pos1.x = p;
	pos1.y = 0;
	pos1.num_col = ft_get_size_windz();
	pos1.cmd = NULL;
	if (!(pos1.end = ft_memalloc(sizeof(int) * 20)))
		return ;
	pos1.s = s;
	ft_mmmm(&pos1.end);
}
