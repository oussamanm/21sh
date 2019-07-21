/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 12:21:38 by aboukhri          #+#    #+#             */
/*   Updated: 2019/05/19 13:21:28 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "termcap.h"

char	*get_prompt(void)
{
	char	*path;
	char	*dir;
	char	*prompt;

	path = getpwd();
	dir = ft_strdup("\033[1;36m");
	if (ft_chrlen(path, '/') == 1)
		dir = ft_strjoir(dir, "/", 1);
	else
		dir = ft_strjoir(dir, ft_strrchr(path, '/'), 1);
	dir = ft_strjoir(dir, "\033[0m", 1);
	prompt = ft_strjoir(dir, "\033[1;31m ✗ \033[0m", 1);
	free(path);
	return (prompt);
}

void	set_info_termcap(struct s_termcap *info, char *prompt)
{
	int	len;
	struct winsize ws;
	int	li;
	int co;

	ioctl(0, TIOCGWINSZ, &ws);
	info->prompt = prompt;
	len = ft_strlen(info->prompt) - 24;
	li = (len / ws.ws_col) + 1;
	co = (len > ws.ws_col) ? (len - ws.ws_col) : len;
	info->cursor = (struct s_cursor){co, li, len};
}

int		get_col_pos(void)
{
	/*char	buf[30];
	int		i;
	int		pow;
	int		ch;

	ft_bzero(buf, 30);
	write(2, "\033[6n", 4);
	i = 0;
	ch = 0;
	while (ch != 'R')
	{
		(read(0, &ch, 1) > 0) && (buf[i] = ch);
		i++;
	}
	if (i < 2)
		return (-1);
	i -= 1;
	pow = 1;
	ch = 0;
	while (buf[--i] != ';')
	{
		ch = ch + (buf[i] - '0') * pow;
		pow *= 10;
	}*/
	return (8);
}

/*
**	disable and enable canonical & ECHO modes
*/

void	disable_term(void)
{
	int				fd;
	struct termios	term;

	fd = open(ttyname(0), O_RDWR);
	if (isatty(fd))
	{
		tcgetattr(fd, &term);
		term.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(fd, TCSANOW, &term);
	}
	close(fd);
}

void	enable_term(void)
{
	int				fd;
	struct termios	term;

	fd = open(ttyname(0), O_RDWR);
	if (isatty(fd))
	{
		tcgetattr(fd, &term);
		term.c_lflag |= ICANON;
		term.c_lflag |= ECHO;
		tcsetattr(fd, TCSANOW, &term);
	}
	close(fd);
}
