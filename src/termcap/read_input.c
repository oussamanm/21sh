/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 05:40:27 by mfetoui           #+#    #+#             */
/*   Updated: 2019/05/19 13:10:33 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "termcap.h"
#include "../includes/termcap.h"


void	read_input_keys(struct s_termcap *info, char *buff)
{
	int		key;

	key = *((int *)buff);
	if (key == K_RIGHT || key == K_LEFT || key == K_HOME || key == K_END ||
		key == ALT_UP || key == ALT_DOWN || key == ALT_LEFT || key == ALT_RIGHT)
		navigate_keys(key, info);
	else if (key == K_UP || key == K_DOWN || key == K_BACKSPACE ||
		key == CTRL_D || key == CTRL_P || key == CTRL_T || key == CTRL_L)
		edit_keys(key, info);
	else if (key_is_str(buff))
	{
		paste_line(&info->line, &info->cursor, buff);
	}
}

void	set_readline(struct s_termcap *info)
{
	info->content = (char*)ft_memalloc(1);
	(!info->select) && (info->select = (char*)ft_memalloc(1));
	info->line = (char*)ft_memalloc(1);
}

int		read_input(const int fd, struct s_termcap *info, char **env)
{
	char	buff[5];
	int rd;

	(void )env;
	set_readline(info);
	ft_bzero(buff, 5);
	while ((rd = read(fd, buff, 4)) > 0)
	{
		if ((buff[0] == '\t' && !buff[1]))
			auto_complete(info, buff);
		if (buff[0] == '\n' && buff[1] == '\0')
		{
			if (return_key(info))
				break ;
		}
		else if (*((int *)buff) == CTRL_D)
			end_of_life(&info->line, info->cursor, env);
		else
			read_input_keys(info, buff);
		tputs(tgoto(tgetstr("ch", NULL), 0, info->cursor.co), 1, ft_putchar_err);
		ft_bzero(buff, 5);
	}
	ft_strdel(&info->line);
	return ((int)ft_strlen(info->content));
}
