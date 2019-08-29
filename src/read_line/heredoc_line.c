/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhidr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 18:21:28 by hlamhidr          #+#    #+#             */
/*   Updated: 2019/08/03 18:21:30 by hlamhidr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char	*ft_read_heredoc(char *eol)
{
	char		*s;
	char		*line;
	t_history	*his;
	t_select	*select;

	his = NULL;
	select = NULL;
	line = NULL;
	ft_save_address(&his, &select);
	while (1337)
	{
		ft_putstr("heredoc> ");
		s = ft_read_line(his, select, 9);
		if (ft_strequ(s, eol) || (s != NULL && s[0] == -1))
		{
			ft_strdel(&s);
			break ;
		}
		(!line) ? (line = ft_strnew(0)) : 0;
		(!s) ? (s = ft_strnew(0)) : 0;
		line = ft_strjoir(line, s, 3);
		line = ft_strjoir(line, "\n", 1);
	}
	return (line);
}
