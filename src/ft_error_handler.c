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

int		ft_error_separ(char *str_arg, char c) /// return 1 : error
{
	int	temp;

	temp = 0;
	while (*str_arg)
	{
		if (*str_arg == c)
		{
			if (temp)
				return (1);
			str_arg++;
			continue ;
			temp = 1;
		}
		if (temp == 1 && (*str_arg == ' ' || *str_arg == '\t'))
		{
			str_arg++;
			continue ;
		}
		else if (temp == 1)
			temp = 0;
		str_arg++;
	}
	return (0);
}

/*
int		ft_error_redir(char *str_arg)
{
	int i;
	int quote;
	int temp;
	
	quote = 0;
	if (!str_arg)
		return (1);
	i = -1;
	while (str_arg[++i])
	{
		if (str_arg[i] == '\'' || str_arg[i] == '"') /// in case of quote escape it
			if ((temp = ft_find_char(&str_arg[i + 1], str_arg[i])) != -1)
				i += temp;
		temp = 0;
		if (str_arg[i] == '>' || str_arg[i] == '<')
		{
			if (str_arg[i + 1] == str_arg[i] && ++temp)
				i++;
			while (str_arg[i] != '\0' && ft_isspace(str_arg[i])) /// escape whitespaces
				i++;
			if (!ft_isalphanum(str_arg[i]))
				return (1);
			if (!ft_isprint(str_arg[i]))
				return (1);
		}
	}
}
*/
void	ft_print_error(char *msg, char *para1, char *para2, int rm)
{
	if (msg == NULL)
	{
		ft_putstr("Opss MSG_ERROR is NULL \n");
		return ;
	}
	if (para1 != NULL)
		ft_putstr_fd(para1, 2);
	if (para2 != NULL)
		ft_putstr_fd(para2, 2);
	if (para2 != NULL)
		ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	if (rm == 1 || rm == 3)
		ft_strdel(&para1);
	if (rm == 2 || rm == 3)
		ft_strdel(&para2);
	return ;
}