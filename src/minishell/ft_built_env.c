/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:04 by onouaman          #+#    #+#             */
/*   Updated: 2019/05/03 18:51:07 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_builtenv_cmd(char **args, char ***env)
{
	int	j;

	j = 0;
	if (ft_str_alphanum(args[j]) == 0)
	{
		if (access(args[j], F_OK) == -1)
			ft_print_error(FIL_NS, "env: ", args[j], 0);
		else if (access(args[j], X_OK) == 0)
		{
			if (ft_call_child(&args[j], *env, 1) == -1)
				ft_putstr("Ops there's an error in child process\n");
		}
		else
			ft_print_error(FIL_PD, "env: ", args[j], 0);
	}
	else
	{
		j = ft_check_built(args, env);
		j = (j == 0) ? ft_call_child(args, *env, 0) : j;
		(j == -1) ? ft_print_error(FIL_NS, "env: ", *args, 0) : NULL;
	}
}

void		ft_buil_env(char **args, char ***env)
{
	int		j;
	char	**new_env;

	if (*env == NULL)
		return ;
	j = 0;
	while (args[j] != NULL && ft_find_char(args[j], '=') > 0)
		j++;
	new_env = ft_strr_dup(*env, ft_strrlen(*env));
	(j != 0) ? ft_buil_setenv(args, &new_env, j) : NULL;
	if (args[j] != NULL)
		ft_builtenv_cmd(&args[j], &new_env);
	if (args[j] == NULL)
	{
		ft_put_strr(*env);
		if (j != 0 && !(j = 0))
			ft_put_strr(new_env);
	}
	ft_strrdel(new_env);
}

void		ft_buil_setenv(char **args, char ***env, int len_args)
{
	if (*env == NULL || *args == NULL)
		return ;
	while (len_args-- != 0 && *args != NULL)
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
		if (ft_strncmp(arg, (*env)[i], len_arg - 1) == 0)
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
