/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:04 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 04:24:20 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void		ft_buil_env(char **args, char ***env)
{
	int		i;

	i = 0;
	if (env != NULL && *env != NULL)
		ft_put_strr(*env);
	while (args != NULL && args[i] != NULL)
	{
		if (ft_find_char(args[i], '=') > 0)
			ft_putendl(args[i]);
		else
			break ;
		i++;
	}
}

void		ft_buil_setenv(char **args, char ***env)
{
	if (env == NULL || args == NULL || *args == NULL)
		return ;
	while (*args != NULL)
	{
		if (ft_find_char(*args, '=') > 0)
			ft_set_vrb(*args, env, 0);
		else
			ft_print_error(CMD_NV, "setenv :", *args, 0);
		args++;
	}
	return ;
}

void		ft_buil_unsetenv(char *arg, char ***env)
{
	int		len_arg;
	int		i;
	int		len_env;

	len_env = -1;
	if (!(i = 0) && ((*env) == NULL || (*env)[0] == NULL || arg == NULL))
		return ;
	while ((*env)[i] && (*env)[i] != NULL)
	{
		len_arg = ft_find_char((*env)[i], '=');
		len_arg = (len_arg == 1) ? 2 : len_arg;
		if (ft_find_char(arg, '=') >= 0)
			ft_print_error(CMD_NV, "setenv :", arg, 0);
		else if (ft_strncmp(arg, (*env)[i], len_arg) == 0)
		{
			len_env = ft_strrlen(*env);
			ft_strdel(&((*env)[i]));
			break ;
		}
		i++;
	}
	while (i < (len_env - 1) && (*env)[i + 1] != NULL)
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	(*env)[i] = (len_env != -1) ? NULL : (*env)[i];
}
