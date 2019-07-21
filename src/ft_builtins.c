/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 16:45:14 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_buil_echo(char **arg, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	UNUSED(env);
	while (arg[++i] != NULL)
	{
		(j != 0) ? ft_putchar(' ') : NULL;
		j = 0;
		while (arg[i][j] != '\0')
		{
			//if (arg[i][j] == '$' && arg[i][j + 1] != '$' &&
			//		arg[i][j + 1] != '\0')
			//	j += ft_print_var(&arg[i][j + 1], env);
			//if (j == 0 && arg[i][0] == '~' &&
			//		(arg[i][1] == 47 || arg[i][1] == '\0') && ++j)
			//	ft_print_var("HOME", env);
			//else
				ft_putchar(arg[i][j++]);
		}
	}
	ft_putstr("\n");
}

int			ft_error_cd(char *path, char **arg)
{
	int			bl_err;
	struct stat	st_stat;

	bl_err = 0;
	if (arg[0] != NULL && path != NULL && arg[0][0] == '~' &&
			ft_isalpha(arg[0][1]) && access(path, F_OK) == -1 && (bl_err = 1))
		ft_print_error(path, "cd :", FIL_NU, 0);
	else if (ft_strlen(path) >= 1024 && (bl_err = 1))
		ft_print_error(path, "cd :", "MAX PATH", 0);
	else if (access(path, F_OK) == -1 && (bl_err = 1))
		ft_print_error(path, "cd :", FIL_NS, 0);
	else
	{
		stat(path, &st_stat);
		if (!S_ISDIR(st_stat.st_mode) && (bl_err = 1))
			ft_print_error(FIL_ND, "cd :", path, 0);
		else if (access(path, X_OK) == -1 && (bl_err = 1))
			ft_print_error(FIL_PD, "cd :", path, 0);
	}
	return (bl_err);
}

void		ft_buil_cd(char **arg, char ***env)
{
	char	*path;
	char	buff[1024];

	if (*arg == NULL)
		path = ft_get_vrb("HOME", *env);
	else
		path = ft_strdup(arg[0]);
	/*else if ((*arg)[0] == '~' && ft_isalpha((*arg)[1]))
		path = ft_strjoir("/Users/", &(*arg)[1], 0);
	else if ((*arg)[0] == '~' && !ft_isalpha((*arg)[1]))
		path = ft_strjoir(ft_get_vrb("HOME", *env), &(*arg)[1], 1);
	else if (*arg[0] == '$')
	{
		path = ft_get_vrb(&arg[0][1], *env);
		path = (path == NULL) ? ft_get_vrb("HOME", *env) : path;
	}*/

	if (ft_error_cd(path, arg) != 1)
	{
		ft_set_vrb(ft_strjoir("OLDPWD", getcwd(buff, 1024), 0), env, 1);
		chdir(path);
		ft_set_vrb(ft_strjoir("PWD", getcwd(buff, 1024), 0), env, 1);
	}
	ft_strdel(&path);
}

char	*getpwd(void)
{
	char *path;

	path = ft_memalloc(PATHSIZE);
	getcwd(path, PATHSIZE);
	return (path);
}