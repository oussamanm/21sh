/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_minish.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:37 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 06:21:40 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_intia_err(char *tty)
{
	fd_err = 0;
	if ((fd_err = open(tty, O_RDWR)) < 0)
		ft_putstr("Error in Open func with name of tty!\n");
}

void	ft_handler_ctlc(void)
{
	ft_putstr("\n$> ");
}

void	ft_handler_quit(void)
{
	ft_putstr("exit\n");
	exit(0);
}

void	ft_print_error(char *msg, char *para1, char *para2, int rm)
{
	if (msg == NULL)
	{
		ft_putstr("Opss MSG_ERROR is NULL \n");
		return ;
	}
	(para1 != NULL) ? ft_putstr(para1) : NULL;
	(para2 != NULL) ? ft_putstr(para2) : NULL;
	(para2 != NULL) ? ft_putstr(": ") : NULL;
	ft_putendl(msg);
	if (rm == 1 || rm == 3)
		ft_strdel(&para1);
	if (rm == 2 || rm == 3)
		ft_strdel(&para2);
	return ;
}

char	*ft_find_path(char *arg, char **env)
{
	int		i;
	char	**str_paths;
	char	*temp;

	i = -1;
	str_paths = NULL;
	if (env == NULL || arg == NULL)
		return (NULL);
	if (env != NULL && *env != NULL)
	{
		temp = ft_get_vrb("PATH", env);
		str_paths = (temp != NULL) ? ft_str_split(temp, ":") : NULL;
		ft_strdel(&temp);
	}
	while (str_paths != NULL && str_paths[++i] != NULL)
	{
		str_paths[i] = ft_strjoir(str_paths[i], "/", 1);
		temp = ft_strjoir(str_paths[i], arg, 0);
		if (access(temp, F_OK) != 0)
			continue ;
		ft_strrdel(str_paths);
		return (temp);
	}
	ft_strrdel(str_paths);
	return (NULL);
}
