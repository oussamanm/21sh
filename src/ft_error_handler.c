/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:38:33 by onouaman          #+#    #+#             */
/*   Updated: 2019/06/22 16:38:35 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_intia_err(char *tty)
{
	fd_err = 0;
	if ((fd_err = open(tty, O_RDWR)) < 0)
		ft_putstr("Error in Open func with name of tty!\n");
}

void		ft_err_exit(char *str)
{
	ft_putstr(str);
	exit(0);
}

int			ft_error_separ(char *str_arg, char c) /// return 1 : error
{
	int	temp;
	char **args;

	if ((args = ft_str_split_q(str_arg, " ;")) == NULL || args[0] == NULL)
	{
		ft_strrdel(args);
		return (1);
	}
	ft_strrdel(args);
	temp = 0;
	while (*str_arg)
	{
		if (*str_arg == c)
		{
			if (temp)
				return (1);
			str_arg++;
			temp = 1;
			continue ;
		}
		if (temp == 1 && *str_arg != ' ' && *str_arg != '\t')
			temp = 0;
		str_arg++;
	}
	return (0);
}

