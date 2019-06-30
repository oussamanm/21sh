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

#include "21sh.h"

int		get_next_line(const int fd, char **line)
{
	char		*str;
	int			i;
	int			rd;
	char		*temp;

	str = ft_strnew(1);
	temp = ft_strnew(BUFF_SIZE);
	i = 0;
	while ((rd = read(fd, temp, BUFF_SIZE)) != -1)
	{
		temp[rd] = '\0';
		str = ft_strjoir(str, temp, 1);
		ft_bzero(temp, BUFF_SIZE);
		if ((i = ft_find_char(str, '\n')) != -1)
			break ;
	}
	if (i >= 0 && str[i])
		str[i] = '\0';
	*line = str;
	ft_strdel(&temp);
	return (1);
}
