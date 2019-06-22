/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:26:35 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:26:49 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_next_line(const int fd, char **line)
{
	char		*tab;
	int			i;
	int			rd;
	char		*temp;

	tab = ft_strnew(1);
	temp = ft_strnew(BUFF_SIZE);
	i = 0;
	while ((rd = read(fd, temp, BUFF_SIZE)) != -1)
	{
		temp[rd] = '\0';
		tab = ft_strjoir(tab, temp, 1);
		ft_bzero(temp, BUFF_SIZE);
		if ((i = ft_find_char(tab, '\n')) != -1)
			break ;
	}
	if (i >= 0 && tab[i])
		tab[i] = '\0';
	*line = tab;
	ft_strdel(&temp);
	return (1);
}
