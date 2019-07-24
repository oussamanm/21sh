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

int		ft_error_semic(char *str_arg, char **args_cmd) /// return 1 : error
{
	int i;

	while (*str_arg)
	{
		if (*str_arg == ';' && *(str_arg + 1) == ';')
			return (1);
		str_arg++;
	}
	while (*args_cmd != NULL)
	{
		i = 0;
		while ((*args_cmd)[i] && i != -1)
		{
			if (!ft_isspace((*args_cmd)[i]))
				i = -1;
			else
				i++;
		}
		if (i != -1)
			return (1);
		args_cmd++;
	}
	return (0);
}

void	ft_print_error(char *msg, char *para1, char *para2, int rm)
{
	if (msg == NULL)
	{
		ft_putstr("Opss MSG_ERROR is NULL \n");
		return ;
	}
	if (para1 != NULL)
		ft_putstr(para1);
	if (para2 != NULL)
		ft_putstr(para2);
	if (para2 != NULL)
		ft_putstr(": ");
	ft_putendl(msg);
	if (rm == 1 || rm == 3)
		ft_strdel(&para1);
	if (rm == 2 || rm == 3)
		ft_strdel(&para2);
	return ;
}